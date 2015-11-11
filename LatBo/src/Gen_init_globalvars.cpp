#include "../inc/stdafx.h"
#include "../inc/definitions.h"
#include "../inc/globalvars.h"
// File containing global variable initialisations

using namespace std; // Standard namespace in use

// Global initialisation as follows

// Lattice velocities
#if (dims == 3)

	// D3Q19 (defined as in Mawson 2013 thesis but with last column as the rest particle)
	const int c[3][nVels] =
		{
			{1,	-1,  0,  0,  0,  0,  1, -1,  1, -1,  0,  0,  0,  0,  1, -1, -1,  1,  0},
			{0,  0,  1, -1,  0,  0,  1, -1, -1,  1,  1, -1,  1, -1,  0,  0,  0,  0,  0},
			{0,  0,  0,  0,  1, -1,  0,  0,  0,  0,  1, -1, -1,  1,  1, -1,  1, -1,  0}
		};

#else

	// D2Q9
	const int c[3][nVels] =
		{
			{1,	-1,  0,  0,  1, -1,  1, -1,  0},
			{0,  0,  1, -1,  1, -1, -1,  1,  0},
			{0,  0,  0,  0,  0,  0,  0,  0,  0}
		};

#endif


// Weights
#if (dims == 3)

	const double w[nVels] =
		{1.0/18.0, 1.0/18.0, 1.0/18.0, 1.0/18.0, 1.0/18.0, 1.0/18.0,
		1.0/36.0, 1.0/36.0, 1.0/36.0, 1.0/36.0, 1.0/36.0, 1.0/36.0, 1.0/36.0, 1.0/36.0, 1.0/36.0, 1.0/36.0, 1.0/36.0, 1.0/36.0,
		1.0/3.0};

#else

	const double w[nVels] =
		{1.0/9.0, 1.0/9.0, 1.0/9.0, 1.0/9.0, 1.0/36.0, 1.0/36.0, 1.0/36.0, 1.0/36.0, 4.0/9.0};

#endif

// Lattice sound speed
const double cs = 1.0 / sqrt(3.0);

// MRT transformation matrices and their inverses
#if (defined USE_MRT && dims == 3)

	// D3Q19
	const int mMRT[nVels][nVels] =
		{
			{ 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1},
			{-11,-11,-11,-11,-11,-11, 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8, -30},
			{-4, -4, -4, -4, -4, -4,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  12},
			{ 1, -1,  0,  0,  0,  0,  1, -1,  1, -1,  0,  0,  0,  0,  1, -1, -1,  1,  0},
			{-4,  4,  0,  0,  0,  0,  1, -1,  1, -1,  0,  0,  0,  0,  1, -1, -1,  1,  0},
			{ 0,  0,  1, -1,  0,  0,  1, -1, -1,  1,  1, -1,  1, -1,  0,  0,  0,  0,  0},
			{ 0,  0, -4,  4,  0,  0,  1, -1, -1,  1,  1, -1,  1, -1,  0,  0,  0,  0,  0},
			{ 0,  0,  0,  0,  1, -1,  0,  0,  0,  0,  1, -1, -1,  1,  1, -1,  1, -1,  0},
			{ 0,  0,  0,  0, -4,  4,  0,  0,  0,  0,  1, -1, -1,  1,  1, -1,  1, -1,  0},
			{ 2,  2, -1, -1, -1, -1,  1,  1,  1,  1, -2, -2, -2, -2,  1,  1,  1,  1,  0},
			{-4, -4,  2,  2,  2,  2,  1,  1,  1,  1, -2, -2, -2, -2,  1,  1,  1,  1,  0},
			{ 0,  0,  1,  1, -1, -1,  1,  1,  1,  1,  0,  0,  0,  0, -1, -1, -1, -1,  0},
			{ 0,  0, -2, -2,  2,  2,  1,  1,  1,  1,  0,  0,  0,  0, -1, -1, -1, -1,  0},
			{ 0,  0,  0,  0,  0,  0,  1,  1, -1, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0},
			{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1, -1, -1,  0,  0,  0,  0,  0},
			{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1, -1, -1,  0},
			{ 0,  0,  0,  0,  0,  0,  1, -1,  1, -1,  0,  0,  0,  0, -1,  1,  1, -1,  0},
			{ 0,  0,  0,  0,  0,  0, -1,  1,  1, -1,  1, -1,  1, -1,  0,  0,  0,  0,  0},
			{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1,  1,  1, -1,  1, -1,  1, -1,  0}
		};

	const double mInvMRT[nVels][nVels] =
		{
			{ 1.0/19.0, -11.0/2394.0, -1.0/63.0,   1.0/10.0, -1.0/10.0,	 0.0,		0.0,	   0.0,       0.0,		 1.0/18.0, -1.0/18.0,  0.0,	      0.0,       0.0,      0.0,      0.0,      0.0,      0.0,      0.0 },
			{ 1.0/19.0, -11.0/2394.0, -1.0/63.0,  -1.0/10.0,  1.0/10.0,	 0.0,		0.0,	   0.0,       0.0,		 1.0/18.0, -1.0/18.0,  0.0,       0.0,       0.0,      0.0,      0.0,      0.0,      0.0,      0.0 },
			{ 1.0/19.0, -11.0/2394.0, -1.0/63.0,   0.0,		  0.0,		 1.0/10.0, -1.0/10.0,  0.0,		  0.0,		-1.0/36.0,  1.0/36.0,  1.0/12.0, -1.0/12.0,  0.0,	   0.0,      0.0,      0.0,      0.0,      0.0 },
			{ 1.0/19.0, -11.0/2394.0, -1.0/63.0,   0.0,		  0.0,		-1.0/10.0,	1.0/10.0,  0.0,		  0.0,      -1.0/36.0,  1.0/36.0,  1.0/12.0, -1.0/12.0,	 0.0,	   0.0,      0.0,      0.0,      0.0,      0.0 },
			{ 1.0/19.0, -11.0/2394.0, -1.0/63.0,   0.0,		  0.0,		 0.0,		0.0,	   1.0/10.0, -1.0/10.0, -1.0/36.0,  1.0/36.0, -1.0/12.0,  1.0/12.0,	 0.0,	   0.0,      0.0,      0.0,      0.0,      0.0 },
			{ 1.0/19.0, -11.0/2394.0, -1.0/63.0,   0.0,		  0.0,		 0.0,		0.0,	  -1.0/10.0,  1.0/10.0, -1.0/36.0,  1.0/36.0, -1.0/12.0,  1.0/12.0,	 0.0,	   0.0,      0.0,      0.0,      0.0,      0.0 },
			{ 1.0/19.0,  4.0/1197.0,   1.0/252.0,  1.0/10.0,  1.0/40.0,	 1.0/10.0,	1.0/40.0,  0.0,		  0.0,		 1.0/36.0,  1.0/72.0,  1.0/12.0,  1.0/24.0,	 1.0/4.0,  0.0,      0.0,      1.0/8.0,	-1.0/8.0,  0.0 },
			{ 1.0/19.0,  4.0/1197.0,   1.0/252.0, -1.0/10.0, -1.0/40.0,	-1.0/10.0, -1.0/40.0,  0.0,		  0.0,       1.0/36.0,	1.0/72.0,  1.0/12.0,  1.0/24.0,	 1.0/4.0,  0.0,      0.0,     -1.0/8.0,  1.0/8.0,  0.0 },
			{ 1.0/19.0,  4.0/1197.0,   1.0/252.0,  1.0/10.0,  1.0/40.0,	-1.0/10.0, -1.0/40.0,  0.0,		  0.0,       1.0/36.0,	1.0/72.0,  1.0/12.0,  1.0/24.0,	-1.0/4.0,  0.0,      0.0,      1.0/8.0,  1.0/8.0,  0.0 },
			{ 1.0/19.0,  4.0/1197.0,   1.0/252.0, -1.0/10.0, -1.0/40.0,	 1.0/10.0,	1.0/40.0,  0.0,		  0.0,       1.0/36.0,	1.0/72.0,  1.0/12.0,  1.0/24.0,	-1.0/4.0,  0.0,      0.0,     -1.0/8.0, -1.0/8.0,  0.0 },
			{ 1.0/19.0,  4.0/1197.0,   1.0/252.0,  0.0,		  0.0,		 1.0/10.0,	1.0/40.0,  1.0/10.0,  1.0/40.0, -1.0/18.0, -1.0/36.0,  0.0, 	  0.0,        0.0,     1.0/4.0,  0.0,      0.0,      1.0/8.0, -1.0/8.0 },
			{ 1.0/19.0,  4.0/1197.0,   1.0/252.0,  0.0,		  0.0,		-1.0/10.0, -1.0/40.0, -1.0/10.0, -1.0/40.0, -1.0/18.0, -1.0/36.0,  0.0, 	  0.0, 	      0.0,     1.0/4.0,  0.0,      0.0,     -1.0/8.0,  1.0/8.0 },
			{ 1.0/19.0,  4.0/1197.0,   1.0/252.0,  0.0,		  0.0,		 1.0/10.0,	1.0/40.0, -1.0/10.0, -1.0/40.0, -1.0/18.0, -1.0/36.0,  0.0, 	  0.0, 	      0.0,    -1.0/4.0,  0.0,      0.0,      1.0/8.0,  1.0/8.0 },
			{ 1.0/19.0,  4.0/1197.0,   1.0/252.0,  0.0,		  0.0,		-1.0/10.0, -1.0/40.0,  1.0/10.0,  1.0/40.0, -1.0/18.0, -1.0/36.0,  0.0, 	  0.0, 		  0.0,    -1.0/4.0,  0.0,      0.0,     -1.0/8.0, -1.0/8.0 },
			{ 1.0/19.0,  4.0/1197.0,   1.0/252.0,  1.0/10.0,  1.0/40.0,	 0.0,	    0.0,	   1.0/10.0,  1.0/40.0,  1.0/36.0,  1.0/72.0, -1.0/12.0, -1.0/24.0,	  0.0,     0.0,      1.0/4.0, -1.0/8.0,  0.0,      1.0/8.0 },
			{ 1.0/19.0,  4.0/1197.0,   1.0/252.0, -1.0/10.0, -1.0/40.0,	 0.0,		0.0,	  -1.0/10.0, -1.0/40.0,  1.0/36.0,	1.0/72.0, -1.0/12.0, -1.0/24.0,	  0.0,     0.0,      1.0/4.0,  1.0/8.0,  0.0,     -1.0/8.0 },
			{ 1.0/19.0,  4.0/1197.0,   1.0/252.0, -1.0/10.0, -1.0/40.0,	 0.0,		0.0,	   1.0/10.0,  1.0/40.0,	 1.0/36.0,	1.0/72.0, -1.0/12.0, -1.0/24.0,	  0.0,     0.0,     -1.0/4.0, -1.0/8.0,  0.0,      1.0/8.0 },
			{ 1.0/19.0,  4.0/1197.0,   1.0/252.0,  1.0/10.0,  1.0/40.0,	 0.0,		0.0,	  -1.0/10.0, -1.0/40.0,	 1.0/36.0,	1.0/72.0, -1.0/12.0, -1.0/24.0,	  0.0,     0.0,     -1.0/4.0,  1.0/8.0,  0.0,     -1.0/8.0 },
			{ 1.0/19.0, -5.0/399.0,    1.0/21.0,   0.0,		  0.0,		 0.0,		0.0,	   0.0,		  0.0,       0.0,		0.0,       0.0, 	  0.0,        0.0,     0.0,      0.0,      0.0,      0.0,      0.0 }
		};


#elif (defined USE_MRT && dims == 2)

	// D2Q9
	const int mMRT[nVels][nVels] =
		{
			{ 1,  1,  1,  1,  1,  1,  1,  1,  1},
			{-1, -1, -1, -1,  2,  2,  2,  2, -4},
			{-2, -2, -2, -2,  1,  1,  1,  1,  4},
			{ 1, -1,  0,  0,  1, -1,  1, -1,  0},
			{-2,  2,  0,  0,  1, -1,  1, -1,  0},
			{ 0,  0,  1, -1,  1, -1, -1,  1,  0},
			{ 0,  0, -2,  2,  1, -1, -1,  1,  0},
			{ 1,  1, -1, -1,  0,  0,  0,  0,  0},
			{ 0,  0,  0,  0,  1,  1, -1, -1,  0}
		};

	const double mInvMRT[nVels][nVels] =
		{
			{ 4.0/36.0,	 -1.0/36.0, -2.0/36.0,  6.0/36.0, -6.0/36.0,  0.0,       0.0,       9.0/36.0,  0.0 },
			{ 4.0/36.0,	 -1.0/36.0, -2.0/36.0, -6.0/36.0,  6.0/36.0,  0.0,       0.0,       9.0/36.0,  0.0 },
			{ 4.0/36.0,	 -1.0/36.0, -2.0/36.0,  0.0,       0.0,       6.0/36.0, -6.0/36.0, -9.0/36.0,  0.0 },
			{ 4.0/36.0,	 -1.0/36.0, -2.0/36.0,  0.0,       0.0,      -6.0/36.0,  6.0/36.0, -9.0/36.0,  0.0 },
			{ 4.0/36.0,	  2.0/36.0,  1.0/36.0,  6.0/36.0,  3.0/36.0,  6.0/36.0,  3.0/36.0,  0.0,       9.0/36.0 },
			{ 4.0/36.0,	  2.0/36.0,  1.0/36.0, -6.0/36.0, -3.0/36.0, -6.0/36.0, -3.0/36.0,  0.0,       9.0/36.0 },
			{ 4.0/36.0,	  2.0/36.0,  1.0/36.0,  6.0/36.0,  3.0/36.0, -6.0/36.0, -3.0/36.0,  0.0,      -9.0/36.0 },
			{ 4.0/36.0,	  2.0/36.0,  1.0/36.0, -6.0/36.0, -3.0/36.0,  6.0/36.0,  3.0/36.0,  0.0,      -9.0/36.0 },
			{ 4.0/36.0,  -4.0/36.0,  4.0/36.0,  0.0,       0.0,       0.0,       0.0,       0.0,       0.0 }
		};

#endif

// Get the time and convert it to a serial stamp for the output directory creation
time_t curr_time = time(NULL);	// Current system date/time
struct tm* timeinfo = localtime (&curr_time);
char timeout_char [80];
size_t ignore = strftime (timeout_char, 80, "./output_%F_%H-%M-%S", timeinfo);
string timeout_str (timeout_char);
