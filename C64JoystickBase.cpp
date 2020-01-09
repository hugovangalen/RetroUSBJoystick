#include "C64JoystickBase.h"


/**
 * The `MAX_DATA_QUEUE` determines the size of the 
 * ring-buffer to catch changes while we are 
 * processing them.
 * 
 * The value can probably be tweaked way down.
 */
#define MAX_DATA_QUEUE 1024


/**
 * The `_pointer` is only assigned when we're 
 * configured to use interrupts.
 */
static C64JoystickBase *_pointer = NULL;


/**
 * Ring-buffer...
 */
volatile uint32_t _dataWriteIndex = 0;
volatile uint32_t _dataReadIndex = 0;
uint8_t _dataQueue[ MAX_DATA_QUEUE ];


/**
 * This initialises the data-queue which is used to
 * catch pin changes while we may be busy processing
 * them.
 */
void clearDataQueue()
{
    memset( _dataQueue, 0xFF, sizeof(_dataQueue) );
    
    _dataReadIndex = 0;
    _dataWriteIndex = 0;
}


#ifdef C64_USE_INTERRUPTS

volatile bool _inHandler = false;

/**
 * This will trigger an update of the button state.
 */
static void interruptHandler()
{
    if (_inHandler) return;
    
    _inHandler = true;
    
    _dataQueue[ _dataWriteIndex ] = _pointer->read();
    _dataWriteIndex++;

    if (_dataWriteIndex == MAX_DATA_QUEUE)
    {
        _dataWriteIndex = 0;
    }
    
    _inHandler = false;
}


ISR(PCINT0_vect)
{
    interruptHandler();
}

ISR(INT0_vect)
{
    interruptHandler();
}

ISR(INT1_vect)
{
    interruptHandler();
}


#endif

void C64JoystickBase::begin()
{
#ifndef C64_USE_PORTS
    for (uint8_t iter=0; iter < _C64_MAX_BUTTONS; iter++)
    {
        pinMode( _pins[ iter ], INPUT_PULLUP );
    }

    if (_irq) 
    {
        _pointer = this;    
        /* for (uint8_t iter=0; iter < _C64_MAX_BUTTONS; iter++)
        {
            attachInterrupt( digitalPinToInterrupt( _pins[iter] ), interruptHandler, CHANGE );
        } */
    }
    else
    {
        _pointer = NULL;
    }
    
#else
    _pointer = this;    
    
    _C64_DDRUDL |= _C64_MASKUDL;
    _C64_PORTUDL |= _C64_MASKUDL; // enable pull-ups
    
    _C64_DDRRF |= _C64_MASKRF;
    _C64_PORTRF |= _C64_MASKRF;

    
#ifdef C64_USE_INTERRUPTS
    clearDataQueue();
    
    cli();
    
    PCICR = _BV(PCIE0);
    PCMSK0 = _BV(PCINT4) | _BV(PCINT5) | _BV(PCINT6) | _BV(PCINT7);
    
    EICRA = (EICRA & ~((1<<ISC00) | (1<<ISC01))) | (CHANGE << ISC00);
    EIMSK |= _BV(INT0);
    
    EICRA = (EICRA & ~((1<<ISC10) | (1<<ISC11))) | (CHANGE << ISC10);
    EIMSK |= _BV(INT1);
    
    sei();
    
#endif /* C64_USE_INTERRUPTS */
    
#endif /* C64_USE_PORTS */
    
    // Set an initial invalid value to detect changes.
    _buttonState = 0xFF;        
}


uint8_t C64JoystickBase::get()
{
    return _buttonState;
}

uint8_t C64JoystickBase::read() 
{
#ifdef C64_USE_PORTS
    
    //uint8_t udl = (_C64_PINUDL >> 4); // (0b00000111 & (_C64_PINUDL >> 4));
    //DEBUG( "UDL: " );
    //DEBUGBIN( udl );
    //uint8_t rf =  (_C64_PINRF << 3); // (0b00011000 & (_C64_PINRF << 3));
    
    //DEBUG( ", RF: " );
    //DEBUGBIN( rf );
    //uint8_t newState = ~( 0b11100000 | udl | rf );
    
    uint8_t newState = ~( 0b11100000 | (_C64_PINUDL >> 4) | (_C64_PINRF << 3) );
    
    //DEBUG( ", newState: " );
    //DEBUGBIN( newState );
    //newState = ~newState;
    
    //DEBUG( "buttonState: " );
    //DEBUGBIN( newState );
    //DEBUG( "\n" );
    
#else 

    uint8_t newState = 0;
    
    for (uint8_t iter = 0; iter < _C64_MAX_BUTTONS; iter++)
    {            
        if (digitalRead( _pins[ iter ] ) == LOW)
        {  
            newState |= (1 << iter);
        }
        
    }

#endif /* C64_USE_PORTS */

#ifdef C64_JOYSTICK_TEST
    DEBUG( "newState: " );
    DEBUGBIN( newState );
    DEBUG( "\n" );
#endif
    
    return newState;
    
} // read()



/**
 * This updates the _buttonState and returns `true` if it has
 * changed since last time.
 */
bool C64JoystickBase::update() 
{
    uint8_t newState;
    
#ifndef C64_USE_INTERRUPTS
    
    newState = read();
    
#else
    
    if (_irq)
    {
        newState = _dataQueue[ _dataReadIndex ];
        if (newState == 0xFF)
        {
            return false;
        }
        
        _dataQueue[ _dataReadIndex ] = 0xFF; // invalidate after use
        _dataReadIndex++;
        
        if (_dataReadIndex == MAX_DATA_QUEUE)
        {
            _dataReadIndex = 0;
        }
    }
    else
    {
        newState = read();
    }
    
#endif /* C64_USE_INTERRUPTS */

    if (newState != _buttonState)
    {
        _buttonState = newState;
        
#ifdef SERIAL_DEBUG
        
        Serial.print( "buttonState: " );
        for(uint8_t i = 8 ; i > 0 ; i--)
        {
            uint8_t test = 1 << (i-1);
            Serial.print( _buttonState & test ? "1":"0" );
        }
        Serial.println();
#endif
        
        return true;
    }
    
    return false;
    
} // bool update()



/**
 * This method allows external updates (for example when
 * receiving wireless data.
 */
void C64JoystickBase::set( uint8_t state )
{
    _buttonState = state;
}

