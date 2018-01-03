#pragma once

class Vector3
{
	float x_, y_, z_;
public:
	Vector3(float x, float y, float z) { x_ = x; y_ = y; z_ = z; };
	const Vector3 zeroVector = Vector3(0,0,0);
};

/*
 public const float kEpsilon = 1E-05f;

		public float x;

		public float y;

		public float z;

		private static readonly Vector3 zeroVector = new Vector3(0f, 0f, 0f);

		private static readonly Vector3 oneVector = new Vector3(1f, 1f, 1f);

		private static readonly Vector3 upVector = new Vector3(0f, 1f, 0f);

		private static readonly Vector3 downVector = new Vector3(0f, -1f, 0f);

		private static readonly Vector3 leftVector = new Vector3(-1f, 0f, 0f);

		private static readonly Vector3 rightVector = new Vector3(1f, 0f, 0f);

		private static readonly Vector3 forwardVector = new Vector3(0f, 0f, 1f);

		private static readonly Vector3 backVector = new Vector3(0f, 0f, -1f);

		private static readonly Vector3 positiveInfinityVector = new Vector3(float.PositiveInfinity, float.PositiveInfinity, float.PositiveInfinity);

		private static readonly Vector3 negativeInfinityVector = new Vector3(float.NegativeInfinity, float.NegativeInfinity, float.NegativeInfinity);

		public float this[int index]
		{
			get
			{
				float result;
				switch (index)
				{
				case 0:
					result = this.x;
					break;
				case 1:
					result = this.y;
					break;
				case 2:
					result = this.z;
					break;
				default:
					throw new IndexOutOfRangeException("Invalid Vector3 index!");
				}
				return result;
			}
			set
			{
				switch (index)
				{
				case 0:
					this.x = value;
					break;
				case 1:
					this.y = value;
					break;
				case 2:
					this.z = value;
					break;
				default:
					throw new IndexOutOfRangeException("Invalid Vector3 index!");
				}
			}
		}

		public Vector3 normalized
		{
			get
			{
				return Vector3.Normalize(this);
			}
		}

		public float magnitude
		{
			get
			{
				return Mathf.Sqrt(this.x * this.x + this.y * this.y + this.z * this.z);
			}
		}

		public float sqrMagnitude
		{
			get
			{
				return this.x * this.x + this.y * this.y + this.z * this.z;
			}
		}

		public static Vector3 zero
		{
			get
			{
				return Vector3.zeroVector;
			}
		}

		public static Vector3 one
		{
			get
			{
				return Vector3.oneVector;
			}
		}

		public static Vector3 forward
		{
			get
			{
				return Vector3.forwardVector;
			}
		}

		public static Vector3 back
		{
			get
			{
				return Vector3.backVector;
			}
		}

		public static Vector3 up
		{
			get
			{
				return Vector3.upVector;
			}
		}

		public static Vector3 down
		{
			get
			{
				return Vector3.downVector;
			}
		}

		public static Vector3 left
		{
			get
			{
				return Vector3.leftVector;
			}
		}

		public static Vector3 right
		{
			get
			{
				return Vector3.rightVector;
			}
		}

		public static Vector3 positiveInfinity
		{
			get
			{
				return Vector3.positiveInfinityVector;
			}
		}

		public static Vector3 negativeInfinity
		{
			get
			{
				return Vector3.negativeInfinityVector;
			}
		}

		[Obsolete("Use Vector3.forward instead.")]
		public static Vector3 fwd
		{
			get
			{
				return new Vector3(0f, 0f, 1f);
			}
		}

		public Vector3(float x, float y, float z)
		{
			this.x = x;
			this.y = y;
			this.z = z;
		}

		public Vector3(float x, float y)
		{
			this.x = x;
			this.y = y;
			this.z = 0f;
		}

		[ThreadAndSerializationSafe]
		public static Vector3 Slerp(Vector3 a, Vector3 b, float t)
		{
			Vector3 result;
			Vector3.INTERNAL_CALL_Slerp(ref a, ref b, t, out result);
			return result;
		}

		[GeneratedByOldBindingsGenerator]
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void INTERNAL_CALL_Slerp(ref Vector3 a, ref Vector3 b, float t, out Vector3 value);

		public static Vector3 SlerpUnclamped(Vector3 a, Vector3 b, float t)
		{
			Vector3 result;
			Vector3.INTERNAL_CALL_SlerpUnclamped(ref a, ref b, t, out result);
			return result;
		}

		[GeneratedByOldBindingsGenerator]
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void INTERNAL_CALL_SlerpUnclamped(ref Vector3 a, ref Vector3 b, float t, out Vector3 value);

		private static void Internal_OrthoNormalize2(ref Vector3 a, ref Vector3 b)
		{
			Vector3.INTERNAL_CALL_Internal_OrthoNormalize2(ref a, ref b);
		}

		[GeneratedByOldBindingsGenerator]
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void INTERNAL_CALL_Internal_OrthoNormalize2(ref Vector3 a, ref Vector3 b);

		private static void Internal_OrthoNormalize3(ref Vector3 a, ref Vector3 b, ref Vector3 c)
		{
			Vector3.INTERNAL_CALL_Internal_OrthoNormalize3(ref a, ref b, ref c);
		}

		[GeneratedByOldBindingsGenerator]
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void INTERNAL_CALL_Internal_OrthoNormalize3(ref Vector3 a, ref Vector3 b, ref Vector3 c);

		public static void OrthoNormalize(ref Vector3 normal, ref Vector3 tangent)
		{
			Vector3.Internal_OrthoNormalize2(ref normal, ref tangent);
		}

		public static void OrthoNormalize(ref Vector3 normal, ref Vector3 tangent, ref Vector3 binormal)
		{
			Vector3.Internal_OrthoNormalize3(ref normal, ref tangent, ref binormal);
		}

		public static Vector3 RotateTowards(Vector3 current, Vector3 target, float maxRadiansDelta, float maxMagnitudeDelta)
		{
			Vector3 result;
			Vector3.INTERNAL_CALL_RotateTowards(ref current, ref target, maxRadiansDelta, maxMagnitudeDelta, out result);
			return result;
		}

		[GeneratedByOldBindingsGenerator]
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void INTERNAL_CALL_RotateTowards(ref Vector3 current, ref Vector3 target, float maxRadiansDelta, float maxMagnitudeDelta, out Vector3 value);

		[Obsolete("Use Vector3.ProjectOnPlane instead.")]
		public static Vector3 Exclude(Vector3 excludeThis, Vector3 fromThat)
		{
			return fromThat - Vector3.Project(fromThat, excludeThis);
		}

		public static Vector3 Lerp(Vector3 a, Vector3 b, float t)
		{
			t = Mathf.Clamp01(t);
			return new Vector3(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t);
		}

		public static Vector3 LerpUnclamped(Vector3 a, Vector3 b, float t)
		{
			return new Vector3(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t);
		}

		public static Vector3 MoveTowards(Vector3 current, Vector3 target, float maxDistanceDelta)
		{
			Vector3 a = target - current;
			float magnitude = a.magnitude;
			Vector3 result;
			if (magnitude <= maxDistanceDelta || magnitude < 1.401298E-45f)
			{
				result = target;
			}
			else
			{
				result = current + a / magnitude * maxDistanceDelta;
			}
			return result;
		}

		[ExcludeFromDocs]
		public static Vector3 SmoothDamp(Vector3 current, Vector3 target, ref Vector3 currentVelocity, float smoothTime, float maxSpeed)
		{
			float deltaTime = Time.deltaTime;
			return Vector3.SmoothDamp(current, target, ref currentVelocity, smoothTime, maxSpeed, deltaTime);
		}

		[ExcludeFromDocs]
		public static Vector3 SmoothDamp(Vector3 current, Vector3 target, ref Vector3 currentVelocity, float smoothTime)
		{
			float deltaTime = Time.deltaTime;
			float maxSpeed = float.PositiveInfinity;
			return Vector3.SmoothDamp(current, target, ref currentVelocity, smoothTime, maxSpeed, deltaTime);
		}

		public static Vector3 SmoothDamp(Vector3 current, Vector3 target, ref Vector3 currentVelocity, float smoothTime, [DefaultValue("Mathf.Infinity")] float maxSpeed, [DefaultValue("Time.deltaTime")] float deltaTime)
		{
			smoothTime = Mathf.Max(0.0001f, smoothTime);
			float num = 2f / smoothTime;
			float num2 = num * deltaTime;
			float d = 1f / (1f + num2 + 0.48f * num2 * num2 + 0.235f * num2 * num2 * num2);
			Vector3 vector = current - target;
			Vector3 vector2 = target;
			float maxLength = maxSpeed * smoothTime;
			vector = Vector3.ClampMagnitude(vector, maxLength);
			target = current - vector;
			Vector3 vector3 = (currentVelocity + num * vector) * deltaTime;
			currentVelocity = (currentVelocity - num * vector3) * d;
			Vector3 vector4 = target + (vector + vector3) * d;
			if (Vector3.Dot(vector2 - current, vector4 - vector2) > 0f)
			{
				vector4 = vector2;
				currentVelocity = (vector4 - vector2) / deltaTime;
			}
			return vector4;
		}

		public void Set(float newX, float newY, float newZ)
		{
			this.x = newX;
			this.y = newY;
			this.z = newZ;
		}

		public static Vector3 Scale(Vector3 a, Vector3 b)
		{
			return new Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
		}

		public void Scale(Vector3 scale)
		{
			this.x *= scale.x;
			this.y *= scale.y;
			this.z *= scale.z;
		}

		public static Vector3 Cross(Vector3 lhs, Vector3 rhs)
		{
			return new Vector3(lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x);
		}

		public override int GetHashCode()
		{
			return this.x.GetHashCode() ^ this.y.GetHashCode() << 2 ^ this.z.GetHashCode() >> 2;
		}

		public override bool Equals(object other)
		{
			bool result;
			if (!(other is Vector3))
			{
				result = false;
			}
			else
			{
				Vector3 vector = (Vector3)other;
				result = (this.x.Equals(vector.x) && this.y.Equals(vector.y) && this.z.Equals(vector.z));
			}
			return result;
		}

		public static Vector3 Reflect(Vector3 inDirection, Vector3 inNormal)
		{
			return -2f * Vector3.Dot(inNormal, inDirection) * inNormal + inDirection;
		}

		public static Vector3 Normalize(Vector3 value)
		{
			float num = Vector3.Magnitude(value);
			Vector3 result;
			if (num > 1E-05f)
			{
				result = value / num;
			}
			else
			{
				result = Vector3.zero;
			}
			return result;
		}

		public void Normalize()
		{
			float num = Vector3.Magnitude(this);
			if (num > 1E-05f)
			{
				this /= num;
			}
			else
			{
				this = Vector3.zero;
			}
		}

		public static float Dot(Vector3 lhs, Vector3 rhs)
		{
			return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
		}

		public static Vector3 Project(Vector3 vector, Vector3 onNormal)
		{
			float num = Vector3.Dot(onNormal, onNormal);
			Vector3 result;
			if (num < Mathf.Epsilon)
			{
				result = Vector3.zero;
			}
			else
			{
				result = onNormal * Vector3.Dot(vector, onNormal) / num;
			}
			return result;
		}

		public static Vector3 ProjectOnPlane(Vector3 vector, Vector3 planeNormal)
		{
			return vector - Vector3.Project(vector, planeNormal);
		}

		public static float Angle(Vector3 from, Vector3 to)
		{
			return Mathf.Acos(Mathf.Clamp(Vector3.Dot(from.normalized, to.normalized), -1f, 1f)) * 57.29578f;
		}

		public static float SignedAngle(Vector3 from, Vector3 to, Vector3 axis)
		{
			Vector3 normalized = from.normalized;
			Vector3 normalized2 = to.normalized;
			float num = Mathf.Acos(Mathf.Clamp(Vector3.Dot(normalized, normalized2), -1f, 1f)) * 57.29578f;
			float num2 = Mathf.Sign(Vector3.Dot(axis, Vector3.Cross(normalized, normalized2)));
			return num * num2;
		}

		public static float Distance(Vector3 a, Vector3 b)
		{
			Vector3 vector = new Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
			return Mathf.Sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
		}

		public static Vector3 ClampMagnitude(Vector3 vector, float maxLength)
		{
			Vector3 result;
			if (vector.sqrMagnitude > maxLength * maxLength)
			{
				result = vector.normalized * maxLength;
			}
			else
			{
				result = vector;
			}
			return result;
		}

		public static float Magnitude(Vector3 vector)
		{
			return Mathf.Sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
		}

		public static float SqrMagnitude(Vector3 vector)
		{
			return vector.x * vector.x + vector.y * vector.y + vector.z * vector.z;
		}

		public static Vector3 Min(Vector3 lhs, Vector3 rhs)
		{
			return new Vector3(Mathf.Min(lhs.x, rhs.x), Mathf.Min(lhs.y, rhs.y), Mathf.Min(lhs.z, rhs.z));
		}

		public static Vector3 Max(Vector3 lhs, Vector3 rhs)
		{
			return new Vector3(Mathf.Max(lhs.x, rhs.x), Mathf.Max(lhs.y, rhs.y), Mathf.Max(lhs.z, rhs.z));
		}

		public static Vector3 operator +(Vector3 a, Vector3 b)
		{
			return new Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
		}

		public static Vector3 operator -(Vector3 a, Vector3 b)
		{
			return new Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
		}

		public static Vector3 operator -(Vector3 a)
		{
			return new Vector3(-a.x, -a.y, -a.z);
		}

		public static Vector3 operator *(Vector3 a, float d)
		{
			return new Vector3(a.x * d, a.y * d, a.z * d);
		}

		public static Vector3 operator *(float d, Vector3 a)
		{
			return new Vector3(a.x * d, a.y * d, a.z * d);
		}

		public static Vector3 operator /(Vector3 a, float d)
		{
			return new Vector3(a.x / d, a.y / d, a.z / d);
		}

		public static bool operator ==(Vector3 lhs, Vector3 rhs)
		{
			return Vector3.SqrMagnitude(lhs - rhs) < 9.99999944E-11f;
		}

		public static bool operator !=(Vector3 lhs, Vector3 rhs)
		{
			return !(lhs == rhs);
		}

		public override string ToString()
		{
			return UnityString.Format("({0:F1}, {1:F1}, {2:F1})", new object[]
			{
				this.x,
				this.y,
				this.z
			});
		}

		public string ToString(string format)
		{
			return UnityString.Format("({0}, {1}, {2})", new object[]
			{
				this.x.ToString(format),
				this.y.ToString(format),
				this.z.ToString(format)
			});
		}

		[Obsolete("Use Vector3.Angle instead. AngleBetween uses radians instead of degrees and was deprecated for this reason")]
		public static float AngleBetween(Vector3 from, Vector3 to)
		{
			return Mathf.Acos(Mathf.Clamp(Vector3.Dot(from.normalized, to.normalized), -1f, 1f));
		}
 */