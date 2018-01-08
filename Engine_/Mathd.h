#pragma once
#include <limits>
#include <cstdint>
//#include "Color.h"
#include <vector>
#include <cfloat>
#include <math.h>

# define M_PIl          3.141592653589793238462643383279502884197169399375105820974L /* pi */

/**
 * \brief A collection of common math functions.
 */
class Mathd {
public:
	/**
	 * \brief A tiny floating point value (Read Only).
	 */
	const double Epsilon = ~(1LL << 52);
	//3.141592653589793238462643383279502884197169399375105820974

	/**
	 * \brief The infamous 3.14159265358979... value (Read Only).
	 */
	const double PI = M_PIl;
	//const double PI = 3.141592653589793238462643383279502884197169399375105820974;

	/**
	 * \brief A representation of positive infinity (Read Only).
	 */
	const double Infinity = DBL_MAX;

	/**
	 * \brief A representation of negative infinity (Read Only).
	 */
	const double NegativeInfinity = DBL_MIN;


	/**
	 * \brief Degrees-to-radians conversion constant (Read Only).
	 */
	const double Deg2Rad = 0.017453292519943295769236907684886127134428718885417254560L;

	/**
	 * \brief Radians-to-degrees conversion constant (Read Only).
	 */
	const double Rad2Deg = 57.29577951308232087679815481410517033240547246656432154916L;


	/**
	 * \brief Returns the closest power of two value.
	 * \param value
	 * \return Returns the closest power of two value.
	 */
	static uint32_t ClosestPowerOfTwo(uint32_t value);

	/**
	* \brief Returns the next power of two value.
	* \param value
	* \return
	*/
	static uint32_t NextPowerOfTwo(uint32_t v);

	

	/**
	 * \brief Returns true if the value is power of two.
	 * \param value 
	 * \return true if the value is power of two.
	 */
	static bool IsPowerOfTwo(uint32_t value);
	
	/**
	 * \brief Generate 2D Perlin noise.
	 * \param x X-coordinate of sample point.
	 * \param y Y-coordinate of sample point.
	 * \return Value between 0.0 and 1.0.
	 */
	static double PerlinNoise(double x, double y);

	static int16_t FloatToHalf(float val);

	static float HalfToFloat(int16_t val);

	/**
	 * \brief Returns the sine of angle f in radians.
	 * \param f The argument as a radian.
	 * \return The return value between -1 and +1.
	 */
	static float Sin(float f);

	/**
	 * \brief Returns the cosine of angle f in radians.
	 * \param f 
	 * \return 
	 */
	static float Cos(float f);

	/**
	 * \brief Returns the tangent of angle f in radians.
	 * \param f 
	 * \return 
	 */
	static float Tan(float f);

	/**
	 * \brief Returns the arc-sine of f - the angle in radians whose sine is f.
	 * \param f 
	 * \return 
	 */
	static float Asin(float f);

	/**
	 * \brief Returns the arc-cosine of f - the angle in radians whose cosine is f.
	 * \param f 
	 * \return 
	 */
	static float Acos(float f);

	/**
	 * \brief Returns the arc-tangent of f - the angle in radians whose tangent is f.
	 * \param f 
	 * \return 
	 */
	static float Atan(float f);

	/**
	 * \brief Returns the angle in radians whose Tan is y/x.
	 * \param y 
	 * \param x 
	 * \return 
	 */
	static float Atan2(float y, float x);

	/**
	 * \brief Returns square root of f.
	 * \param f 
	 * \return 
	 */
	static float Sqrt(float f);

	/**
	 * \brief Returns the absolute value of f.
	 * \param f 
	 * \return 
	 */
	static float Abs(float f);

	/**
	 * \brief Returns the absolute value of value.
	 * \param value 
	 * \return 
	 */
	static int32_t Abs(int32_t value);

	/**
	 * \brief Returns the smallest of two or more values.
	 * \param a 
	 * \param b 
	 * \return 
	 */
	static double Min(double a, double b);

	/**
	 * \brief Returns the smallest of two or more values.
	 * \param values 
	 * \return 
	 */
	static double Min(std::vector<double> values);

	/**
	 * \brief Returns the smallest of two values.
	 * \param a 
	 * \param b 
	 * \return 
	 */
	static int32_t Min(int32_t a, int32_t b);

	/**
	 * \brief Returns the smallest of two or more values.
	 * \param values 
	 * \return 
	 */
	static int32_t Min(std::vector<int32_t> values);

	/**
	* \brief Returns the largest of two or more values.
	* \param a
	* \param b
	* \return
	*/
	static double Max(double a, double b);

	/**
	* \brief Returns the largest of two or more values.
	* \param values
	* \return
	*/
	static double Max(std::vector<double> values);

	/**
	* \brief Returns the largest of two values.
	* \param a
	* \param b
	* \return
	*/
	static int32_t Max(int32_t a, int32_t b);

	/**
	* \brief Returns the largest of two or more values.
	* \param values
	* \return
	*/
	static int32_t Max(std::vector<int32_t> values);


	/**
	 * \brief Returns f raised to power p. 
	 * \param f 
	 * \param p 
	 * \return 
	 */
	static double Pow(double f, double p);

};

	/*
		

		

		/// <summary>
		///   <para>Returns e raised to the specified power.</para>
		/// </summary>
		/// <param name="power"></param>
		public static float Exp(float power)
		{
			return (float)Math.Exp((double)power);
		}

		/// <summary>
		///   <para>Returns the logarithm of a specified number in a specified base.</para>
		/// </summary>
		/// <param name="f"></param>
		/// <param name="p"></param>
		public static float Log(float f, float p)
		{
			return (float)Math.Log((double)f, (double)p);
		}

		/// <summary>
		///   <para>Returns the natural (base e) logarithm of a specified number.</para>
		/// </summary>
		/// <param name="f"></param>
		public static float Log(float f)
		{
			return (float)Math.Log((double)f);
		}

		/// <summary>
		///   <para>Returns the base 10 logarithm of a specified number.</para>
		/// </summary>
		/// <param name="f"></param>
		public static float Log10(float f)
		{
			return (float)Math.Log10((double)f);
		}

		/// <summary>
		///   <para>Returns the smallest integer greater to or equal to f.</para>
		/// </summary>
		/// <param name="f"></param>
		public static float Ceil(float f)
		{
			return (float)Math.Ceiling((double)f);
		}

		/// <summary>
		///   <para>Returns the largest integer smaller to or equal to f.</para>
		/// </summary>
		/// <param name="f"></param>
		public static float Floor(float f)
		{
			return (float)Math.Floor((double)f);
		}

		/// <summary>
		///   <para>Returns f rounded to the nearest integer.</para>
		/// </summary>
		/// <param name="f"></param>
		public static float Round(float f)
		{
			return (float)Math.Round((double)f);
		}

		/// <summary>
		///   <para>Returns the smallest integer greater to or equal to f.</para>
		/// </summary>
		/// <param name="f"></param>
		public static int CeilToInt(float f)
		{
			return (int)Math.Ceiling((double)f);
		}

		/// <summary>
		///   <para>Returns the largest integer smaller to or equal to f.</para>
		/// </summary>
		/// <param name="f"></param>
		public static int FloorToInt(float f)
		{
			return (int)Math.Floor((double)f);
		}

		/// <summary>
		///   <para>Returns f rounded to the nearest integer.</para>
		/// </summary>
		/// <param name="f"></param>
		public static int RoundToInt(float f)
		{
			return (int)Math.Round((double)f);
		}

		/// <summary>
		///   <para>Returns the sign of f.</para>
		/// </summary>
		/// <param name="f"></param>
		public static float Sign(float f)
		{
			return (double)f < 0.0 ? -1f : 1f;
		}

		/// <summary>
		///   <para>Clamps a value between a minimum float and maximum float value.</para>
		/// </summary>
		/// <param name="value"></param>
		/// <param name="min"></param>
		/// <param name="max"></param>
		public static float Clamp(float value, float min, float max)
		{
			if ((double)value < (double)min)
				value = min;
			else if ((double)value >(double) max)
				value = max;
			return value;
		}

		/// <summary>
		///   <para>Clamps value between min and max and returns value.</para>
		/// </summary>
		/// <param name="value"></param>
		/// <param name="min"></param>
		/// <param name="max"></param>
		public static int Clamp(int value, int min, int max)
		{
			if (value < min)
				value = min;
			else if (value > max)
				value = max;
			return value;
		}

		/// <summary>
		///   <para>Clamps value between 0 and 1 and returns value.</para>
		/// </summary>
		/// <param name="value"></param>
		public static float Clamp01(float value)
		{
			if ((double)value < 0.0)
				return 0.0f;
			if ((double)value > 1.0)
				return 1f;
			return value;
		}

		/// <summary>
		///   <para>Linearly interpolates between a and b by t.</para>
		/// </summary>
		/// <param name="a">The start value.</param>
		/// <param name="b">The end value.</param>
		/// <param name="t">The interpolation value between the two floats.</param>
		/// <returns>
		///   <para>The interpolated float result between the two float values.</para>
		/// </returns>
		public static float Lerp(float a, float b, float t)
		{
			return a + (b - a) * Mathf.Clamp01(t);
		}

		/// <summary>
		///   <para>Linearly interpolates between a and b by t with no limit to t.</para>
		/// </summary>
		/// <param name="a">The start value.</param>
		/// <param name="b">The end value.</param>
		/// <param name="t">The interpolation between the two floats.</param>
		/// <returns>
		///   <para>The float value as a result from the linear interpolation.</para>
		/// </returns>
		public static float LerpUnclamped(float a, float b, float t)
		{
			return a + (b - a) * t;
		}

		/// <summary>
		///   <para>Same as Lerp but makes sure the values interpolate correctly when they wrap around 360 degrees.</para>
		/// </summary>
		/// <param name="a"></param>
		/// <param name="b"></param>
		/// <param name="t"></param>
		public static float LerpAngle(float a, float b, float t)
		{
			float num = Mathf.Repeat(b - a, 360f);
			if ((double)num > 180.0)
				num -= 360f;
			return a + num * Mathf.Clamp01(t);
		}

		/// <summary>
		///   <para>Moves a value current towards target.</para>
		/// </summary>
		/// <param name="current">The current value.</param>
		/// <param name="target">The value to move towards.</param>
		/// <param name="maxDelta">The maximum change that should be applied to the value.</param>
		public static float MoveTowards(float current, float target, float maxDelta)
		{
			if ((double)Mathf.Abs(target - current) <= (double)maxDelta)
				return target;
			return current + Mathf.Sign(target - current) * maxDelta;
		}

		/// <summary>
		///   <para>Same as MoveTowards but makes sure the values interpolate correctly when they wrap around 360 degrees.</para>
		/// </summary>
		/// <param name="current"></param>
		/// <param name="target"></param>
		/// <param name="maxDelta"></param>
		public static float MoveTowardsAngle(float current, float target, float maxDelta)
		{
			float num = Mathf.DeltaAngle(current, target);
			if (-(double)maxDelta < (double)num && (double)num < (double)maxDelta)
				return target;
			target = current + num;
			return Mathf.MoveTowards(current, target, maxDelta);
		}

		/// <summary>
		///   <para>Interpolates between min and max with smoothing at the limits.</para>
		/// </summary>
		/// <param name="from"></param>
		/// <param name="to"></param>
		/// <param name="t"></param>
		public static float SmoothStep(float from, float to, float t)
		{
			t = Mathf.Clamp01(t);
			t = (float)(-2.0 * (double)t * (double)t * (double)t + 3.0 * (double)t * (double)t);
			return (float)((double)to * (double)t + (double)from * (1.0 - (double)t));
		}

		public static float Gamma(float value, float absmax, float gamma)
		{
			bool flag = false;
			if ((double)value < 0.0)
				flag = true;
			float num1 = Mathf.Abs(value);
			if ((double)num1 >(double) absmax)
				return !flag ? num1 : -num1;
			float num2 = Mathf.Pow(num1 / absmax, gamma) * absmax;
			return !flag ? num2 : -num2;
		}

		/// <summary>
		///   <para>Compares two floating point values and returns true if they are similar.</para>
		/// </summary>
		/// <param name="a"></param>
		/// <param name="b"></param>
		public static bool Approximately(float a, float b)
		{
			return (double)Mathf.Abs(b - a) < (double)Mathf.Max(1E-06f * Mathf.Max(Mathf.Abs(a), Mathf.Abs(b)), Mathf.Epsilon * 8f);
		}

		[ExcludeFromDocs]
		public static float SmoothDamp(float current, float target, ref float currentVelocity, float smoothTime, float maxSpeed)
		{
			float deltaTime = Time.deltaTime;
			return Mathf.SmoothDamp(current, target, ref currentVelocity, smoothTime, maxSpeed, deltaTime);
		}

		[ExcludeFromDocs]
		public static float SmoothDamp(float current, float target, ref float currentVelocity, float smoothTime)
		{
			float deltaTime = Time.deltaTime;
			float maxSpeed = float.PositiveInfinity;
			return Mathf.SmoothDamp(current, target, ref currentVelocity, smoothTime, maxSpeed, deltaTime);
		}

		public static float SmoothDamp(float current, float target, ref float currentVelocity, float smoothTime, [DefaultValue("Mathf.Infinity")] float maxSpeed, [DefaultValue("Time.deltaTime")] float deltaTime)
		{
			smoothTime = Mathf.Max(0.0001f, smoothTime);
			float num1 = 2f / smoothTime;
			float num2 = num1 * deltaTime;
			float num3 = (float)(1.0 / (1.0 + (double)num2 + 0.479999989271164 * (double)num2 * (double)num2 + 0.234999999403954 * (double)num2 * (double)num2 * (double)num2));
			float num4 = current - target;
			float num5 = target;
			float max = maxSpeed * smoothTime;
			float num6 = Mathf.Clamp(num4, -max, max);
			target = current - num6;
			float num7 = (currentVelocity + num1 * num6) * deltaTime;
			currentVelocity = (currentVelocity - num1 * num7) * num3;
			float num8 = target + (num6 + num7) * num3;
			if ((double)num5 - (double)current > 0.0 == (double)num8 > (double)num5)
			{
				num8 = num5;
				currentVelocity = (num8 - num5) / deltaTime;
			}
			return num8;
		}

		[ExcludeFromDocs]
		public static float SmoothDampAngle(float current, float target, ref float currentVelocity, float smoothTime, float maxSpeed)
		{
			float deltaTime = Time.deltaTime;
			return Mathf.SmoothDampAngle(current, target, ref currentVelocity, smoothTime, maxSpeed, deltaTime);
		}

		[ExcludeFromDocs]
		public static float SmoothDampAngle(float current, float target, ref float currentVelocity, float smoothTime)
		{
			float deltaTime = Time.deltaTime;
			float maxSpeed = float.PositiveInfinity;
			return Mathf.SmoothDampAngle(current, target, ref currentVelocity, smoothTime, maxSpeed, deltaTime);
		}

		public static float SmoothDampAngle(float current, float target, ref float currentVelocity, float smoothTime, [DefaultValue("Mathf.Infinity")] float maxSpeed, [DefaultValue("Time.deltaTime")] float deltaTime)
		{
			target = current + Mathf.DeltaAngle(current, target);
			return Mathf.SmoothDamp(current, target, ref currentVelocity, smoothTime, maxSpeed, deltaTime);
		}

		/// <summary>
		///   <para>Loops the value t, so that it is never larger than length and never smaller than 0.</para>
		/// </summary>
		/// <param name="t"></param>
		/// <param name="length"></param>
		public static float Repeat(float t, float length)
		{
			return Mathf.Clamp(t - Mathf.Floor(t / length) * length, 0.0f, length);
		}

		/// <summary>
		///   <para>PingPongs the value t, so that it is never larger than length and never smaller than 0.</para>
		/// </summary>
		/// <param name="t"></param>
		/// <param name="length"></param>
		public static float PingPong(float t, float length)
		{
			t = Mathf.Repeat(t, length * 2f);
			return length - Mathf.Abs(t - length);
		}

		/// <summary>
		///   <para>Calculates the linear parameter t that produces the interpolant value within the range [a, b].</para>
		/// </summary>
		/// <param name="a"></param>
		/// <param name="b"></param>
		/// <param name="value"></param>
		public static float InverseLerp(float a, float b, float value)
		{
			if ((double)a != (double)b)
				return Mathf.Clamp01((float)(((double)value - (double)a) / ((double)b - (double)a)));
			return 0.0f;
		}

		/// <summary>
		///   <para>Calculates the shortest difference between two given angles given in degrees.</para>
		/// </summary>
		/// <param name="current"></param>
		/// <param name="target"></param>
		public static float DeltaAngle(float current, float target)
		{
			float num = Mathf.Repeat(target - current, 360f);
			if ((double)num > 180.0)
				num -= 360f;
			return num;
		}

		internal static bool LineIntersection(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, ref Vector2 result)
		{
			float num1 = p2.x - p1.x;
			float num2 = p2.y - p1.y;
			float num3 = p4.x - p3.x;
			float num4 = p4.y - p3.y;
			float num5 = (float)((double)num1 * (double)num4 - (double)num2 * (double)num3);
			if ((double)num5 == 0.0)
				return false;
			float num6 = p3.x - p1.x;
			float num7 = p3.y - p1.y;
			float num8 = (float)((double)num6 * (double)num4 - (double)num7 * (double)num3) / num5;
			result = new Vector2(p1.x + num8 * num1, p1.y + num8 * num2);
			return true;
		}

		internal static bool LineSegmentIntersection(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, ref Vector2 result)
		{
			float num1 = p2.x - p1.x;
			float num2 = p2.y - p1.y;
			float num3 = p4.x - p3.x;
			float num4 = p4.y - p3.y;
			float num5 = (float)((double)num1 * (double)num4 - (double)num2 * (double)num3);
			if ((double)num5 == 0.0)
				return false;
			float num6 = p3.x - p1.x;
			float num7 = p3.y - p1.y;
			float num8 = (float)((double)num6 * (double)num4 - (double)num7 * (double)num3) / num5;
			if ((double)num8 < 0.0 || (double)num8 > 1.0)
				return false;
			float num9 = (float)((double)num6 * (double)num2 - (double)num7 * (double)num1) / num5;
			if ((double)num9 < 0.0 || (double)num9 > 1.0)
				return false;
			result = new Vector2(p1.x + num8 * num1, p1.y + num8 * num2);
			return true;
		}

		internal static long RandomToLong(System.Random r)
		{
			byte[] buffer = new byte[8];
			r.NextBytes(buffer);
			return (long)BitConverter.ToUInt64(buffer, 0) & long.MaxValue;
		}
	}
}
*/