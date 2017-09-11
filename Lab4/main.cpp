#include "draw.h"
#include "XTime.h"

XTime timer;

int main()
{
	RS_Initialize(REZ_X, REZ_Y);

	timer.Restart();

	original.v1 = { -0.25,  0.5, -0.25, 1.0f };
	original.v2 = { 0.25,  0.5, -0.25, 1.0f };
	original.v3 = { -0.25,  0  , -0.25, 1.0f };
	original.v4 = { 0.25,  0  , -0.25, 1.0f };
	original.v5 = { -0.25,  0.5,  0.25, 1.0f };
	original.v6 = { 0.25,  0.5,  0.25, 1.0f };
	original.v7 = { -0.25,  0  ,  0.25, 1.0f };
	original.v8 = { 0.25,  0  ,  0.25, 1.0f };

	for (unsigned int i = 0; i < 11; ++i)
	{
		gridTop[i].x = i * 0.1f - 0.5f;
		gridTop[i].y = 0.0;
		gridTop[i].z = 0.5;
		gridTop[i].w = 1;

		gridLeft[i].x = -0.5;
		gridLeft[i].y = 0.0;
		gridLeft[i].z = i * 0.1f - 0.5f;
		gridLeft[i].w = 1;


		gridBottom[i].x = i * 0.1f - 0.5f;
		gridBottom[i].y = 0;
		gridBottom[i].z = -0.5;
		gridBottom[i].w = 1;

		gridRight[i].x = 0.5;
		gridRight[i].y = 0.0;
		gridRight[i].z = i * 0.1f - 0.5f;
		gridRight[i].w = 1;
	}
	matrix4 r = matrix4Xrot(-18.0*RADS);
	vec3f v = { 0, 0, -1 };
	matrix4 t = matrix4trans(v);

	matrix4 cameraMatrix = matrix4Multiply(t, r);
	SV_ViewMatrix = matrix4Inverse(cameraMatrix);

	SV_PerspectiveMatrix = perspectiveMatrix(90, 16 / 9, 0.1, 10);

	float theta = 0;

	while (RS_Update(myArray, REZ_X*REZ_Y))
	{
		clearBuffer(0x00000000);

		timer.Signal();
		theta += (float)timer.Delta();

		VertexShader = VS_World;
		PixelShader = PS_Green;

		SV_WorldMatrix = identiyMatrix();
		for (unsigned int i = 0; i < 11; i++)
		{
			drawLine(gridTop[i], gridBottom[i]);
			drawLine(gridLeft[i], gridRight[i]);
		}


		PixelShader = PS_Yellow;
		SV_WorldMatrix = matrix4Yrot(theta);



		drawLine(original.v1, original.v2);
		drawLine(original.v2, original.v4);
		drawLine(original.v4, original.v3);
		drawLine(original.v3, original.v1);

		drawLine(original.v5, original.v6);
		drawLine(original.v6, original.v8);
		drawLine(original.v8, original.v7);
		drawLine(original.v7, original.v5);

		drawLine(original.v1, original.v5);
		drawLine(original.v2, original.v6);
		drawLine(original.v4, original.v8);
		drawLine(original.v3, original.v7);
	}


	RS_Shutdown();
	return 0;
}



///////////////////////////////////////////////////
//												 //
//					NOTES						 //
//												 //
///////////////////////////////////////////////////
/*

---Video 2---
	NDC will now be our final destination
	We're going to start in a general 3d space, everything we define will be in this virtual space
	Worry about the screen later

3D local space (object space) (model space)
	before we do anything to our vertecies they will be concidered to be in local space
	the relationship to verticies to each other
		in relation to the original set of axiis

3D global space (parent space)
	don't confuse with world space

3D World Space
	Defines the space where 3D objects are relative to one another
	defines objects in relation to each other


--Video 3--
	Local vs Global operations



Every mesh should have its own world matrix

HOW TO 3D
1. create a mesh in local space
2. create a world matrix for the mesh
3. repeat steps 1 and 2 for each mesh
4. Build a worl space camera matrix
5. View matrix = inverse of camera matrix


6. Build your projection matrix
7. In shaders, declare global world view projection (wvp)
8. Write 3D vertex shader
9. Set vertex shader, pixel shader
10. Draw

*/
