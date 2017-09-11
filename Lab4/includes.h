#pragma once


struct vec3f
{
	union
	{
		float coord[3];
		struct
		{
			float x, y, z;
		};
	};
};

struct vec4f
{
	union
	{
		float coord[4];
		struct
		{
			float x, y, z, w;
		};
	};
};

//struct with vec4f and color

struct matrix3
{
	union
	{
		float members[9];
		struct
		{
			float Xx, Xy, Xz;
			float Yx, Yy, Yz;
			float Zx, Zy, Zz;
		};
	};
};

struct matrix4
{
	union
	{
		float members[16];
		float twoD[4][4];
		struct
		{
			float Xx, Xy, Xz, Xt;
			float Yx, Yy, Yz, Yt;
			float Zx, Zy, Zz, Zt;
			float Tx, Ty, Tz, Tt;
		};
	};
};

#define REZ_X 500
#define REZ_Y 500

#define RADS 0.01745329251994329576923690768489

unsigned int myArray[REZ_X * REZ_Y];

//cube to create
struct cube
{
	union
	{
		vec4f members[8];
		struct
		{
			//front top
			vec4f v1, v2;
			//front bottom
			vec4f v3, v4;

			//back top
			vec4f v5, v6;
			//back bottom
			vec4f v7, v8;
		};
	};
};

cube original;
cube renderCube;

//vec4f grid[121];
vec4f gridTop[11];
vec4f gridLeft[11];
vec4f gridBottom[11];
vec4f gridRight[11];