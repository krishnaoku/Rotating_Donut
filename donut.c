#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

int k;
double sin(), cos();

int main()
{
    float A = 0, B = 0, i, j, z[1760];
    char b[1760];
    printf("\x1b[2J"); //Clear screen 
    for (;;) { //Infinite loop 
      memset(b, 32, 1760); //Fill b with ASCII space character (32)
      memset(z, 0, 7040); //Fill z with 0
        for (j = 0; 6.28 > j; j += 0.07) { 
            for (i = 0; 6.28 > i; i += 0.02) {
                float sini = sin(i),
                      cosj = cos(j),
                      sinA = sin(A),
                      sinj = sin(j),
                      cosA = cos(A),
                      cosj2 = cosj + 2,
                      brightness = 1 / (sini * cosj2 * sinA + sinj * cosA + 5),
                      cosi = cos(i),
                      cosB = cos(B),
                      sinB = sin(B),
                      t = sini * cosj2 * cosA - sinj * sinA;
                int x = 40 + 30 * brightness * (cosi * cosj2 * cosB - t * sinB), //x coordinate calculation
		  y = 12 + 15 * brightness * (cosi * cosj2 * sinB + t * cosB), //y coordinate calculation
		  o = x + 80 * y, //Calculate index 'o' based on x and y
		  N = 8 * ((sinj * sinA - sini * cosj * cosA) * cosB - sini * cosj * sinA - sinj * cosA - cosi * cosj * sinB);//Calculate character index N
                if (22 > y && y > 0 && x > 0 && 80 > x && brightness > z[o]) {// Check if the point is within visible range and brighter than previous
                    z[o] = brightness; // Update brightness in 'z' array
		    b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0]; //update character in b based on brightness
		    //b[o] = ".........:::"[N > 0 ? N : 0];
                }
            }
        }
        printf("\x1b[d");//move cursor to the beginning of the line
        for (k = 0; 1761 > k; k++)//loop over b
	  putchar(k % 80 ? b[k] : 10);//print characters with line break
        A += 0.04; //increment angle a
	B += 0.02; //increment angle b
        usleep(50000);  // Sleep for 50 ms
    }
    return 0;
}
