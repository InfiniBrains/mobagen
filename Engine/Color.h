#pragma once
#include "Math.h"
#include <string>

struct Color {
private:
	float r;
	float g;
	float b;
	float a;

public:
	// constructors
	Color(float red, float green, float blue, float alpha) {
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}

	Color(float red, float green, float blue) {
		r = red;
		g = green;
		b = blue;
		a = 1.f;
	}

	// static colors
	static Color red() {
		return { 1, 0, 0, 1 };
	}
	static Color green()
	{
		return { 0.f, 1.f, 0.f, 1.f };
	}
	static Color blue()
	{
		return { 0.f, 0.f, 1.f, 1.f };
	}
	static Color white()
	{
		return { 1.f, 1.f, 1.f, 1.f };
	}

	static Color black()
	{
		return { 0.f, 0.f, 0.f, 1.f };
	}
	static Color yellow()
	{
		return { 1.f, 0.921568632f, 0.0156862754f, 1.f };
	}
	static Color cyan()
	{
		return { 0.f, 1.f, 1.f, 1.f };
	}
	static Color magenta()
	{
		return { 1.f, 0.f, 1.f, 1.f };
	}
	static Color gray()
	{
		return { 0.5f, 0.5f, 0.5f, 1.f };
	}
	static Color grey()
	{
		return { 0.5f, 0.5f, 0.5f, 1.f };
	}
	static Color clear()
	{
		return { 0.f, 0.f, 0.f, 0.f };
	}

	// members
	float grayscale()
	{
		return 0.299f * r + 0.587f * g + 0.114f * b;
	}
	Color linear()
	{
		// todo: use mathf instead of math
		return {
			Math::GammaToLinearSpace(this->r), Math::GammaToLinearSpace(this->g), Math::GammaToLinearSpace(this->b), this->a
		};
	}
	Color gamma() {
		// todo: use mathf instead of math
		return{ Math::LinearToGammaSpace(this->r), Math::LinearToGammaSpace(this->g), Math::LinearToGammaSpace(this->b), this->a };
	}
	float maxColorComponent(){
		// todo: use mathf instead of math
		return Math::Max(Math::Max(this->r, this->g), this->b);
	}
	float & operator [](int32_t i)
	{
		// todo: check the if it really change the value when color[i]=value;
		switch (i)
		{
		case 0:
			return r;
		case 1:
			return g;
		case 2:
			return b;
		case 3:
			return a;
		default:
			// todo: exception handling
			return a;
		}
	}

	std::string ToString()
	{
		// todo: make this work properly
		return "todo: make this work properly";

		/*
		return Format("RGBA({0:F3}, {1:F3}, {2:F3}, {3:F3})", new object[]
			{
				this.r,
				this.g,
				this.b,
				this.a
			});
		*/
	}
	/* 
	public string ToString(string format)
	{
		return Format("RGBA({0}, {1}, {2}, {3})", new object[]
			{
				this.r.ToString(format),
				this.g.ToString(format),
				this.b.ToString(format),
				this.a.ToString(format)
			});
	}
	 */
	/*
	public override int GetHashCode()
	{
		return this.GetHashCode();
	}
	*/
};

typedef struct Color Color;
/*
	public override bool Equals(object other)
	{
		bool result;
		if (!(other is Color))
		{
			result = false;
		}
		else
		{
			Color color = (Color)other;
			result = (this.r.Equals(color.r) && this.g.Equals(color.g) && this.b.Equals(color.b) && this.a.Equals(color.a));
		}
		return result;
	}

	public static Color operator +(Color a, Color b)
	{
		return new Color(a.r + b.r, a.g + b.g, a.b + b.b, a.a + b.a);
	}

	public static Color operator -(Color a, Color b)
	{
		return new Color(a.r - b.r, a.g - b.g, a.b - b.b, a.a - b.a);
	}

	public static Color operator *(Color a, Color b)
	{
		return new Color(a.r * b.r, a.g * b.g, a.b * b.b, a.a * b.a);
	}

	public static Color operator *(Color a, float b)
	{
		return new Color(a.r * b, a.g * b, a.b * b, a.a * b);
	}

	public static Color operator *(float b, Color a)
	{
		return new Color(a.r * b, a.g * b, a.b * b, a.a * b);
	}

	public static Color operator /(Color a, float b)
	{
		return new Color(a.r / b, a.g / b, a.b / b, a.a / b);
	}

	public static bool operator ==(Color lhs, Color rhs)
	{
		return lhs == rhs;
	}

	public static bool operator !=(Color lhs, Color rhs)
	{
		return !(lhs == rhs);
	}

	public static Color Lerp(Color a, Color b, float t)
	{
		t = Mathf.Clamp01(t);
		return new Color(a.r + (b.r - a.r) * t, a.g + (b.g - a.g) * t, a.b + (b.b - a.b) * t, a.a + (b.a - a.a) * t);
	}

	public static Color LerpUnclamped(Color a, Color b, float t)
	{
		return new Color(a.r + (b.r - a.r) * t, a.g + (b.g - a.g) * t, a.b + (b.b - a.b) * t, a.a + (b.a - a.a) * t);
	}

	internal Color RGBMultiplied(float multiplier)
	{
		return new Color(this.r * multiplier, this.g * multiplier, this.b * multiplier, this.a);
	}

	internal Color AlphaMultiplied(float multiplier)
	{
		return new Color(this.r, this.g, this.b, this.a * multiplier);
	}

	internal Color RGBMultiplied(Color multiplier)
	{
		return new Color(this.r * multiplier.r, this.g * multiplier.g, this.b * multiplier.b, this.a);
	}

	public static implicit operator Vector4(Color c)
	{
		return new Vector4(c.r, c.g, c.b, c.a);
	}

	public static implicit operator Color(Vector4 v)
	{
		return new Color(v.x, v.y, v.z, v.w);
	}

	public static void RGBToHSV(Color rgbColor, out float H, out float S, out float V)
	{
		if (rgbColor.b > rgbColor.g && rgbColor.b > rgbColor.r)
		{
			Color.RGBToHSVHelper(4f, rgbColor.b, rgbColor.r, rgbColor.g, out H, out S, out V);
		}
		else if (rgbColor.g > rgbColor.r)
		{
			Color.RGBToHSVHelper(2f, rgbColor.g, rgbColor.b, rgbColor.r, out H, out S, out V);
		}
		else
		{
			Color.RGBToHSVHelper(0f, rgbColor.r, rgbColor.g, rgbColor.b, out H, out S, out V);
		}
	}

	private static void RGBToHSVHelper(float offset, float dominantcolor, float colorone, float colortwo, out float H, out float S, out float V)
	{
		V = dominantcolor;
		if (V != 0f)
		{
			float num;
			if (colorone > colortwo)
			{
				num = colortwo;
			}
			else
			{
				num = colorone;
			}
			float num2 = V - num;
			if (num2 != 0f)
			{
				S = num2 / V;
				H = offset + (colorone - colortwo) / num2;
			}
			else
			{
				S = 0f;
				H = offset + (colorone - colortwo);
			}
			H /= 6f;
			if (H < 0f)
			{
				H += 1f;
			}
		}
		else
		{
			S = 0f;
			H = 0f;
		}
	}

	public static Color HSVToRGB(float H, float S, float V)
	{
		return Color.HSVToRGB(H, S, V, true);
	}

	public static Color HSVToRGB(float H, float S, float V, bool hdr)
	{
		Color white = Color.white;
		if (S == 0f)
		{
			white.r = V;
			white.g = V;
			white.b = V;
		}
		else if (V == 0f)
		{
			white.r = 0f;
			white.g = 0f;
			white.b = 0f;
		}
		else
		{
			white.r = 0f;
			white.g = 0f;
			white.b = 0f;
			float num = H * 6f;
			int num2 = (int)Mathf.Floor(num);
			float num3 = num - (float)num2;
			float num4 = V * (1f - S);
			float num5 = V * (1f - S * num3);
			float num6 = V * (1f - S * (1f - num3));
			switch (num2 + 1)
			{
			case 0:
				white.r = V;
				white.g = num4;
				white.b = num5;
				break;
			case 1:
				white.r = V;
				white.g = num6;
				white.b = num4;
				break;
			case 2:
				white.r = num5;
				white.g = V;
				white.b = num4;
				break;
			case 3:
				white.r = num4;
				white.g = V;
				white.b = num6;
				break;
			case 4:
				white.r = num4;
				white.g = num5;
				white.b = V;
				break;
			case 5:
				white.r = num6;
				white.g = num4;
				white.b = V;
				break;
			case 6:
				white.r = V;
				white.g = num4;
				white.b = num5;
				break;
			case 7:
				white.r = V;
				white.g = num6;
				white.b = num4;
				break;
			}
			if (!hdr)
			{
				white.r = Mathf.Clamp(white.r, 0f, 1f);
				white.g = Mathf.Clamp(white.g, 0f, 1f);
				white.b = Mathf.Clamp(white.b, 0f, 1f);
			}
		}
		return white;
	}
}
*/