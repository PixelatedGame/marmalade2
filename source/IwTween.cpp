/*
 * (C) 2001-2013 Marmalade.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "IwTween.h"
#include <stdarg.h>
#include "IwDebug.h"

namespace IwTween {

// Easing functions
// These sit in a namespace called "Ease" so can be copy/pasted
// from OpenQuick's QTween.cpp
namespace Ease {

float linear(float time, float value)
{
    return time;
}
float one(float time, float value)
{
    return 1.0f;
}
float zero(float time, float value)
{
    return 0.0f;
}
float powIn(float time, float power)
{
    if (power == 0.0f) { power = 2.0f; }
    float r = powf(time, power);
    return r;
}
float powOut(float time, float power)
{
    if (power == 0.0f) { power = 2.0f; }
    float r = powf(time, 1 / power);
    return r;
}
float powInOut(float time, float power)
{
    if (power == 0.0f) { power = 2.0f; }
    int sign = 1;
    int r = int(power);
    if (r % 2 == 0)
        sign = -1;

    time *= 2;
    if (time < 1)
        return 0.5f * powf(time, power);
    else
        return sign * 0.5f * (powf(time - 2, power) + sign * 2);
}
float expIn(float time, float value)
{
    if (value == 0.0f) { value = 2.0f; }
    return (time == 0 ? 0 : powf(value, 10 * (time/1 - 1)) - 1 * 0.001f);
}
float expOut(float time, float value)
{
    if (value == 0.0f) { value = 2.0f; }
    return (time == 1 ? 1 : (-powf(value, -10 * time / 1) + 1));
}
float expInOut(float time, float value)
{
    if (value == 0.0f) { value = 2.0f; }
    time *= 2.0f;
    if (time < 1)
        return 0.5f * powf(value, 10 * (time - 1));
    else
        return 0.5f * (-powf(2, -10 * (time - 1)) + 2);
}
float sineIn(float time, float power)
{
    if (power == 0.0f) { power = 1.0f; }
    float r = (-1 * cosf(time * (float)M_PI_2) + 1);
    if (power != 1.0f)
        r = powf(r, power);
    return r;
}
float sineOut(float time, float power)
{
    if (power == 0.0f) { power = 1.0f; }
    float r = (sinf(time * (float)M_PI_2));
    if (power != 1.0f)
        r = powf(r, power);
    return r;
}
float sineInOut(float time, float power)
{
    if (power == 0.0f) { power = 1.0f; }
    float r = (-0.5f * (cosf((float)M_PI * time) - 1));
    if (power != 1.0f)
        r = powf(r, power);
    return r;
}
float elasticIn(float time, float period)
{
    if (period == 0.0f) { period = (float)M_PI * 2.0f; }
    if (time == 0 || time == 1)
        return time;
    else
    {
        float s = period / 4;
        time = time - 1;
        return -powf(2, 10 * time) * sinf((time - s) * M_PI_X_2 / period);
    }
}
float elasticOut(float time, float period)
{
    if (period == 0.0f) { period = (float)M_PI * 2.0f; }
    if (time == 0 || time == 1)
        return time;
    else
    {
        float s = period / 4;
        return powf(2, -10 * time) * sinf((time - s) * M_PI_X_2 / period) + 1;
    }
}
float elasticInOut(float time, float period)
{
    if (period == 0.0f) { period = (float)M_PI * 2.0f; }
    if (time == 0 || time == 1)
        return time;
    else
    {
        time = time * 2;
        if (!period)
            period = 0.3f * 1.5f;

        float s = period / 4;
        time = time - 1;
        if (time < 0)
            return -0.5f * powf(2, 10 * time) * sinf((time -s) * M_PI_X_2 / period);
        else
            return powf(2, -10 * time) * sinf((time - s) * M_PI_X_2 / period) * 0.5f + 1;
    }
}
float _bounceTime(float time)
{
    if (time < 1 / 2.75)
    {
        return 7.5625f * time * time;
    } else
    if (time < 2 / 2.75)
    {
        time -= 1.5f / 2.75f;
        return 7.5625f * time * time + 0.75f;
    } else
    if (time < 2.5 / 2.75)
    {
        time -= 2.25f / 2.75f;
        return 7.5625f * time * time + 0.9375f;
    }
    time -= 2.625f / 2.75f;
    return 7.5625f * time * time + 0.984375f;
}
float bounceIn(float time, float value)
{
    if (value == 0.0f) { value = 1.0f; }
    return 1 - _bounceTime(1 - time);
}
float bounceOut(float time, float value)
{
    if (value == 0.0f) { value = 1.0f; }
    return _bounceTime(1 - time);
}
float bounceInOut(float time, float value)
{
    if (value == 0.0f) { value = 1.0f; }
    if (time < 0.5f)
    {
        time = time * 2;
        return (1 - _bounceTime(1 - time)) * 0.5f;
    }
    else
        return _bounceTime(time * 2 - 1) * 0.5f + 0.5f;
}
float backIn(float time, float value)
{
    if (value == 0.0f) { value = 1.0f; }
    float overshoot = 1.70158f;
    return (time * time * ((overshoot + 1) * time - overshoot));
}
float backOut(float time, float value)
{
    if (value == 0.0f) { value = 1.0f; }
    float overshoot = 1.70158f;
    time = time - 1;
    return (time * time * ((overshoot + 1) * time + overshoot) + 1);
}
float backInOut(float time, float value)
{
    if (value == 0.0f) { value = 1.0f; }
    float overshoot = 1.70158f * 1.525f;
    time = time * 2;
    if (time < 1)
        return ((time * time * ((overshoot + 1) * time - overshoot)) / 2);
    else
    {
        time = time - 2;
        return ((time * time * ((overshoot + 1) * time + overshoot)) / 2 + 1);
    }
}

}; // namespace ease

bool CTween::is_m_Value(void* f_value){
	for (std::vector <ValueType> ::iterator it = m_ValueTypes.begin(); it != m_ValueTypes.end(); ++it)
	{
		if (f_value == it->m_Value){
			return true;
		}
	}
	return false;
}
//------------------------------------------------------------------------------
// CTweenManager
//------------------------------------------------------------------------------
CTween* CTweenManager::Tween(float time, ...)
{
	count++;
    // Add new tween to list, with default spec
    CTween::Spec spec;
    spec.m_Time = time;
    CTween tween(spec);
    m_Tweens.push_back(tween);
    CTween* pTween = &m_Tweens[m_Tweens.size()-1];
    pTween->m_IsTo = true;
    pTween->m_List = this;
	pTween->id = count;

    // Internals
    pTween->m_ElapsedTime = 0.0f;   // total elapsed time on this tween
    pTween->m_IsComplete = false;   // for "clamp": true only when completed
    pTween->m_IsPaused = false;     //
    pTween->m_InProgress = false;   // true only when startTime has elapsed
    pTween->m_NumCycles = 0;        // number of completed cycles

    // Process varargs
    va_list ap;
    va_start(ap, time);

    bool done = false;
    while(done == false)
    {
        Type type = (IwTween::Type)va_arg(ap, int);
        void* target;
        int value;

        IwAssertMsg(TWEEN, type <= END, ("Variable argument list contains illegal CTween::Type value"));
        switch(type)
        {
            // Terminator
            case END:
                done = true;
                break;

            // TO or FROM
            case FROM:
                pTween->m_IsTo = false;
                break;

            case DELAY:
                pTween->m_Spec.m_Delay = (float)va_arg(ap, double);
                break;

            case DELTA:
                pTween->m_Spec.m_Delta = true;
                break;

            case CLAMP:
            case REPEAT:
            case MIRROR:
                pTween->m_Spec.m_Mode = type;
                break;

            case EASING:
                pTween->m_Spec.m_Easing = va_arg(ap, CTween::EasingFn);
                break;
//guyhod
				/*
			case TWEEN:
				pTween->p_ctween = va_arg(ap, CTween**);
				break;
			*/

            case EASINGVALUE:
                pTween->m_Spec.m_EasingValue = (float)va_arg(ap, double);
                break;

            case ONSTART:
                pTween->m_Spec.m_OnStart = va_arg(ap, CTween::Callback);
                break;

            case ONCOMPLETE:
                pTween->m_Spec.m_OnComplete = va_arg(ap, CTween::Callback);
                break;

            // Interpolants
            default:
                target = va_arg(ap, void*);
                switch(type)
                {
                case BOOL:
                    {
                    bool v[4];
                    v[0] = (va_arg(ap, int) != 0);
                    value = *(int*)v;
                    }
                    break;
                case BYTE:
                    {
                    signed char v[4];
                    v[0] = (signed char)va_arg(ap, int);
                    value = *(int*)v;
                    }
                    break;
                case UBYTE:
                    {
                    unsigned char v[4];
                    v[0] = (unsigned char)va_arg(ap, int);
                    value = *(int*)v;
                    }
                    break;
                case SHORT:
                    {
                    short v[2];
                    v[0] = (short)va_arg(ap, int);
                    value = *(int*)v;
                    }
                    break;
                case USHORT:
                    {
                    unsigned short v[2];
                    v[0] = (unsigned short)va_arg(ap, int);
                    value = *(int*)v;
                    }
                    break;
                case INT:
                    {
                    int v = (int)va_arg(ap, int);
                    value = *(int*)&v;
                    }
                    break;
                case UINT:
                    {
                    unsigned int v = (unsigned int)va_arg(ap, int);
                    value = *(int*)&v;
                    }
                    break;
                case FLOAT:
                    {
                    float v = (float)va_arg(ap, double);
                    value = *(int*)&v;
                    }
                    break;

                default:
                    IwAssertMsg(TWEEN, false, ("Unknown type"));
                    break;
                }
                pTween->m_ValueTypes.push_back(CTween::ValueType(type, target, value));
                break;
        }
    }
    va_end(ap);
    return pTween;
}
//------------------------------------------------------------------------------
void CTweenManager::kill_this(int tween_id){
	for (std::vector<CTween>::iterator it = m_Tweens.begin(); it != m_Tweens.end(); it++){
		if (it->id == tween_id){
			it->Cancel();
		}
	}
}
//------------------------------------------------------------------------------
void CTweenManager::Update(float dt)
{
    std::vector<CTween>::iterator itT = m_Tweens.begin();
    for (; itT != m_Tweens.end();)
    {
        if  (
            (itT->m_IsComplete == false) &&
            (itT->m_IsPaused == false)
            )
        {
            bool cancel = itT->Update(dt);
            if (cancel == true)
                m_Tweens.erase(itT);
            else
                ++itT;
        }
        else
            ++itT;
    }
}

//------------------------------------------------------------------------------
// CTween::ValueType
//------------------------------------------------------------------------------
void CTween::ValueType::SetFromCurrentValue(void* pStart, void* pInput, bool isDelta)
{
    // For TO: pStart is snapshot value now, pInput was input value ("TO" value or delta)
    switch(m_Type)
    {
    case BOOL:
        *(bool*)pStart = *(bool*)m_Value;
        break;
    case BYTE:
        *(signed char*)pStart = *(signed char*)m_Value;
        *(signed char*)pInput += isDelta ? *(signed char*)pStart : 0;
        break;
    case UBYTE:
        *(unsigned char*)pStart = *(unsigned char*)m_Value;
        *(unsigned char*)pInput += isDelta ? *(unsigned char*)pStart : 0;
        break;
    case SHORT:
        *(short*)pStart = *(short*)m_Value;
        *(short*)pInput += isDelta ? *(short*)pStart : 0;
        break;
    case USHORT:
        *(unsigned short*)pStart = *(unsigned short*)m_Value;
        *(unsigned short*)pInput += isDelta ? *(unsigned short*)pStart : 0;
        break;
    case INT:
        *(int*)pStart = *(int*)m_Value;
        *(int*)pInput += isDelta ? *(int*)pStart : 0;
        break;
    case UINT:
        *(unsigned int*)pStart = *(unsigned int*)m_Value;
        *(unsigned int*)pInput += isDelta ? *(unsigned int*)pStart : 0;
        break;
    case FLOAT:
        *(float*)pStart = *(float*)m_Value;
        *(float*)pInput += isDelta ? *(float*)pStart : 0.0f;
        break;
    default:
        // ignore
        break;
    }
}
//------------------------------------------------------------------------------
void CTween::ValueType::SetFromInterp(float interp)
{
    switch(m_Type)
    {
    case BOOL:
        *(bool*)m_Value = (interp == 1.0f) ? *(bool*)&m_ValueInput : *(bool*)&m_ValueStart;
        break;
    case BYTE:
        {
        float vd = (float)*(signed char*)&m_ValueInput - (float)*(signed char*)&m_ValueStart;
        *(signed char*)m_Value = (signed char)((*(signed char*)&m_ValueStart) + (interp * vd));
        }
        break;
    case UBYTE:
        {
        float vd = (float)*(unsigned char*)&m_ValueInput - (float)*(unsigned char*)&m_ValueStart;
        *(unsigned char*)m_Value = (unsigned char)((*(unsigned char*)&m_ValueStart) + (interp * vd));
        }
        break;
    case SHORT:
        {
        float vd = (float)*(short*)&m_ValueInput - (float)*(short*)&m_ValueStart;
        *(short*)m_Value = (short)((*(short*)&m_ValueStart) + (interp * vd));
        }
        break;
    case USHORT:
        {
        float vd = (float)*(unsigned short*)&m_ValueInput - (float)*(unsigned short*)&m_ValueStart;
        *(unsigned short*)m_Value = (unsigned short)((*(unsigned short*)&m_ValueStart) + (interp * vd));
        }
        break;
    case INT:
        {
        int vd = *(int*)&m_ValueInput - *(int*)&m_ValueStart;
        *(int*)m_Value = (*(int*)&m_ValueStart) + (int)(interp * vd);
        }
        break;
    case UINT:
        {
        int vd = *(unsigned int*)&m_ValueInput - *(unsigned int*)&m_ValueStart;
        *(unsigned int*)m_Value = (unsigned int)((*(unsigned int*)&m_ValueStart) + (interp * vd));
        }
        break;
    case FLOAT:
        *(float*)m_Value = *(float*)&m_ValueStart + (float)(interp * (*(float*)&m_ValueInput - *(float*)&m_ValueStart));
        break;
    default:
        // ignore
        break;
    }
}

//------------------------------------------------------------------------------
// CTween::Spec
//------------------------------------------------------------------------------
CTween::Spec::Spec()
{
    // Default Spec settings
    m_Time = 1.0f;
    m_Delay = 0.0f;
    m_Delta = false;
    m_Mode = CLAMP;
    m_Easing = Ease::linear;
    m_EasingValue = 0.0f;
    m_OnStart = NULL;
    m_OnComplete = NULL;
}

//------------------------------------------------------------------------------
// CTween
//------------------------------------------------------------------------------
void CTween::Cancel()
{
	if (alive){
		alive = false;
		m_List->m_Tweens.erase(this);
	}
}


//------------------------------------------------------------------------------
bool CTween::Update(float dt)
{
    // dt is delta time
    // m_ElapsedTime is time elapsed on the tween
    // m_Spec.delay is time that tween is supposed to start
    // m_Spec.time is duration of tween
    if (m_IsComplete == true)
        return true;

    // Elapse time, return if animation not yet started (due to 'delay')
    m_ElapsedTime += dt;
    if (m_ElapsedTime < m_Spec.m_Delay)
    {
        // Tween not yet in progress (due to specified delay value)
        return false;
    }

    // Tween in progress
    // Calculate 'frac' value in range 0..1
    float frac = (m_ElapsedTime - (m_Spec.m_Time * m_NumCycles) - m_Spec.m_Delay) / m_Spec.m_Time; // 0..1
    bool cycled = false;
    if (m_Spec.m_Mode != CLAMP) // "repeat" or "mirror"
    {
        if (frac >= 1.0f)
        {
            cycled = true;
            frac = frac - (float)(int)frac;
            m_NumCycles = m_NumCycles + 1; // TODO handle big jumps
        }
    }
    else
        frac = std::min(frac, 1.0f);

    // Call interpolation function to map 'frac' to 'interp'
    // interp also in range 0..1
    float interp;

    // Note: handling of "default value" is done at top of each
    // interp function; definition in C++ header is not effectiev
    interp = m_Spec.m_Easing(frac, m_Spec.m_EasingValue);

    if (m_Spec.m_Mode == MIRROR)
    {
        if (m_NumCycles & 0x1) // numCycles is odd
            interp = 1.0f - interp;
    }

    if (m_InProgress == false)
    {
        // Tween just started
        m_InProgress = true;

        // Call 'onStart' callback?
        if (m_Spec.m_OnStart)
            m_Spec.m_OnStart(this);

        // Set up tween to/from values, depending on tween type and delta
        // TO, no delta: from target current values (after 'delay') to INPUT values
        // TO, with delta: from target current values (after 'delay') to same values + INPUT
        // FROM, no delta: from INPUT values, to target current values (after 'delay')
        // FROM, with delta: from INPUT values + target current values (after 'delay'), to target current values (after 'delay')
        std::vector<ValueType>::iterator itV = m_ValueTypes.begin();
        std::vector<ValueType>::iterator etV = m_ValueTypes.end();
        if (m_IsTo == true)
        {
            // TO
            for (; itV != etV; ++itV)
            {
                itV->SetFromCurrentValue((void*)&itV->m_ValueStart, (void*)&itV->m_ValueInput, m_Spec.m_Delta);
            }
        }
        else
        {
            // FROM
            for (; itV != etV; ++itV)
            {
                itV->SetFromCurrentValue((void*)&itV->m_ValueStart, (void*)&itV->m_ValueInput, m_Spec.m_Delta);

                // Dumb 4-byte swap of Start and Input, because this if "FROM" rather than "TO"
                int start = *(int*)&itV->m_ValueStart;
                *(int*)&itV->m_ValueStart = *(int*)&itV->m_ValueInput;
                *(int*)&itV->m_ValueInput = start;
            }
        }
    }

    // Update values
    std::vector<ValueType>::iterator itV = m_ValueTypes.begin();
    std::vector<ValueType>::iterator etV = m_ValueTypes.end();
    for (; itV != etV; ++itV)
    {
        // We are always interp'ing from Start to Input
        itV->SetFromInterp(interp);
    }

    if (m_Spec.m_Mode != CLAMP) // "repeat" or "mirror"
    {
        if (cycled == true)
        {
            // Tween just cycled
            if (m_Spec.m_OnComplete)
                m_Spec.m_OnComplete(this);
        }
    }
    else
    {
        if (frac >= 1.0f)
        {
            // Tween just completed
            m_IsComplete = true;
            if (m_Spec.m_OnComplete)
                m_Spec.m_OnComplete(this);
            return true;
        }
    }

    // Note: if mode is "repeat" or "mirror", tween never finishes.
    // App must store return value from tween creation function, and call
    // tween:cancel() or similar. Alternatively, tween is destroyed when
    // owning object is destroyed
    return false;
}

}; // namespace IwTween
