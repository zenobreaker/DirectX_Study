#pragma once

class FVector2D;
class FPoint
{
public:
	FPoint(void);
	FPoint(int x, int y);

	operator float* ();
	operator const float* ();

	bool operator ==(const FPoint& value2) const;
	bool operator !=(const FPoint& value2) const;

	FVector2D ToVector2();

	std::string ToString();

public:
	const static FPoint Zero;///< 0, 0

	union
	{
		struct
		{
			int X;///< X
			int Y;///< Y
		};

		int P[2];
	};
	
};