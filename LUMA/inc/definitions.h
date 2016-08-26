/*
 * --------------------------------------------------------------
 *
 * ------ Lattice Boltzmann @ The University of Manchester ------
 *
 * -------------------------- L-U-M-A ---------------------------
 *
 *  Copyright (C) 2015, 2016
 *  E-mail contact: info@luma.manchester.ac.uk
 *
 * This software is for academic use only and not available for
 * distribution without written consent.
 *
 */
#define LUMA_VERSION "1.1.0 (WORKING VERSION)"


// Header guard
#ifndef LBM_DEFINITIONS_H
#define LBM_DEFINITIONS_H

// Declarations here
#include <time.h>			// Timing functionality
#include <iostream>			// IO functionality
#include <fstream>			// File functionality
#include <vector>			// Vector template access
#include <iomanip>			// Output precision control
#include <math.h>			// Mathematics
#include <string>			// String template access
#include <mpi.h>			// Enable MPI


/*
*******************************************************************************
**************************** Debugging Options ********************************
*******************************************************************************
*/


//#define L_MEGA_DEBUG				// Debug F, Feq, Macroscopic all in one file -- Warning: Heavy IO which kills performance
//#define L_INC_RECV_LAYER			// Flag to include writing out receiver layer sites in MPI builds
//#define L_DEBUG_STREAM			// Writes out the number and type of streaming operations used to test streaming exclusions
//#define L_MPI_VERBOSE				// Write out the buffers used by MPI plus more setup data
//#define L_IBM_DEBUG				// Write IBM body and matrix data out to text files
//#define L_IBBODY_TRACER			// Write out IBBody positions
//#define L_LD_OUT					// Write out lift and drag (sum x and y forces on Lagrange markers of IBBody)
//#define L_BFL_DEBUG				// Write out BFL marker positions and Q values out to files
//#define L_LOG_TIMINGS				// Write out the initialisation, time step and mpi timings to an output file


/*
*******************************************************************************
************************* Global configuration data ***************************
*******************************************************************************
*/


// Numbers
#define L_PI 3.14159265358979323846

// Using MPI?
#define L_BUILD_FOR_MPI

// Output Options
#define L_out_every 100				// How many timesteps before whole grid output
#define L_output_precision 3		// Precision of output

// Types of output
//#define L_TEXTOUT
#define L_HDF5_OUTPUT

// High frequency output options
//#define L_PROBE_OUTPUT
#define L_out_every_probe 250
const static int nProbes[3] = {3, 3, 3};		// Number of probes in each direction
// Start and End points for planes of probes
const static int xProbeLims[2] = {90, 270};
const static int yProbeLims[2] = {15, 45};
const static int zProbeLims[2] = {30, 120};


// Gravity
//#define GRAVITY_ON
// Expression for the gravity force
#define L_grav_force 1e-10	//( 3 * gUtils.vecnorm(L_u_0x,L_u_0y,L_u_0z) * nu / pow(fabs(L_b_y - L_a_y),2) )
#define L_grav_direction eXDirection	// Gravity direction (Specify using enumeration)

// Initialisation
//#define L_NO_FLOW			// Initialise the domain with no flow
//#define L_RESTARTING		// Initialise the GridObj with quantities read from a restart file
#define L_restart_out_every 10000

// LBM configuration
#define L_USE_KBC_COLLISION


/*
*******************************************************************************
******************************** Time data ************************************
*******************************************************************************
*/

#define L_Timesteps 50000	// Number of time steps


/*
*******************************************************************************
**************************** Domain Dimensions ********************************
*******************************************************************************
*/

// MPI Data
#define L_Xcores 2
#define L_Ycores 2
#define L_Zcores 2	// Set to 1 if doing a 2D problem when using custom MPI sizes

//#define L_USE_CUSTOM_MPI_SIZES

// MPI local grid sizes (Cartesian topolgy numbered in z, y then x directions)
#ifdef L_USE_CUSTOM_MPI_SIZES
	const static size_t xRankSize[L_Xcores*L_Ycores*L_Zcores]		= {50, 50, 50, 50, 350, 350, 350, 350};
	const static size_t yRankSize[L_Xcores*L_Ycores*L_Zcores]		= {20, 20, 130, 130, 20, 20, 130, 130};
	// The following can be arbitrary if doing a 2D problem
	const static size_t zRankSize[L_Xcores*L_Ycores*L_Zcores]		= {20, 30, 20, 30, 20, 30, 20, 30};
#endif


// Lattice properties (in lattice units)
#define L_dims 3	// Number of dimensions to the problem
#define L_N 128		// Number of x lattice sites
#define L_M 64		// Number of y lattice sites
#define L_K 64		// Number of z lattice sites


// Physical dimensions (dictates scaling)
#define L_a_x 0		// Start of domain-x
#define L_b_x 2		// End of domain-x
#define L_a_y 0		// Start of domain-y
#define L_b_y 1		// End of domain-y
#define L_a_z 0		// Start of domain-z
#define L_b_z 1		// End of domain-z


/*
*******************************************************************************
******************************** Fluid Data ***********************************
*******************************************************************************
*/

// Fluid data in lattice units
//#define L_USE_INLET_PROFILE
#define L_u_ref 0.04		// Reference velocity for scaling (mean inlet velocity)
#define L_u_max 0.06		// Max velocity of profile

// If not using an inlet profile, specify values or expressions here
#define L_u_0x L_u_ref		// Initial x-velocity
#define L_u_0y 0			// Initial y-velocity
#define L_u_0z 0			// Initial z-velocity

#define L_rho_in 1			// Initial density
#define L_Re 2000			// Desired Reynolds number

// nu computed based on above selections


/*
*******************************************************************************
****************************** Immersed Boundary ******************************
*******************************************************************************
*/

// Master IBM switches //
//#define L_IBM_ON						// Turn on IBM

//#define L_STOP_EPSILON_RECOMPUTE		// Prevent recomputing of epsilon in an attempt to save time
#define L_CHEAP_NEAREST_NODE_DETECTION	// Perform a nearest-neighbour-type nearest node operation for IBM support calculation
//#define L_VTK_BODY_WRITE				// Write out the bodies to a VTK file

// Read in IB Body from File
//#define L_IBB_FROM_FILE

#ifdef L_IBB_FROM_FILE
	#define L_ibb_on_grid_lev 0		// Provide grid level on which object should be added 
	#define L_ibb_on_grid_reg 0		// Provide grid region on which object should be added
	// Following specified in physical distances
	#define L_start_ibb_x 3.5
	#define L_start_ibb_y 1.5
	#define L_centre_ibb_z 0.0
	#define L_ibb_length 0.5			// The object input is scaled based on this dimension
	#define L_ibb_scale_direction eXDirection	// Scale in this direction (Specify as enumeration)
	#define L_ibb_length_ref 0.5		// Reference length to be used in the definition of Reynolds number
#endif

// Default global properties
#define L_num_markers 19		// Number of Lagrange points (approximately)
#define L_ibb_deform false		// Default deformable property of body to be built (whether it moves or not)
#define L_ibb_flex_rigid false	// Whether a structural calculation needs to be performed on the body


// Switches for inserting certain bodies (enable only one at once!)
//#define L_INSERT_CIRCLE_SPHERE
//#define L_INSERT_RECTANGLE_CUBOID
//#define L_INSERT_BOTH
//#define L_INSERT_FILAMENT
//#define L_INSERT_FILARRAY
//#define L_2D_RIGID_PLATE_IBM
//#define L_2D_PLATE_WITH_FLAP
//#define L_3D_RIGID_PLATE_IBM
//#define L_3D_PLATE_WITH_FLAP

// Physical dimensions of rigid IB body or flexible plate
#define L_ibb_x 75.0		// x Position of body centre
#define L_ibb_y 75.0		// y Position of body centre
#define L_ibb_z 0.0			// z Position of body centre
#define L_ibb_w 10.0		// width (x) of IB body
#define L_ibb_l 10.0		// length (y) of IB body
#define L_ibb_d 0.0			// depth (z) of IB body
#define L_ibb_r 10.0		// radius of IB body

// Physical dimensions of flexible IB filament
#define L_ibb_filament_length 0.2		// length of filament
#define L_ibb_filament_start_x 0.3	// start x position of the filament
#define L_ibb_filament_start_y 0.0	// start y position of the filament
#define L_ibb_filament_start_z 0.0		// start z position of the filament

// Angles of filament or plate
#define L_ibb_angle_vert 90	// Inclination of filament in xy plane
#define L_ibb_angle_horz 0	// Inclination of filament in xz plane

// Boundary conditions of flexible filament or flexible plate
#define L_start_BC 2		// Type of boundary condition at filament start:	0 == free; 1 = simply supported; 2 == clamped
#define L_end_BC 0			// Type of boundary condition at filament end:		0 == free; 1 = simply supported; 2 == clamped

// Mechanical properties of filament
#define L_ibb_delta_rho 1.0		// Difference in density (lattice units) between solid and fluid
#define L_ibb_EI 2.0			// Flexural rigidity (lattice units) of filament


/*
*******************************************************************************
********************************** Wall Data **********************************
*******************************************************************************
*/

// Virtual Wind Tunnels
//#define L_VIRTUAL_WINDTUNNEL		// Adds a symmetry condition to the ceiling and inlet on floor
//#define L_FLAT_PLATE_TUNNEL			// Adds an inlet to all faces except exit
#define L_FREESTREAM_TUNNEL			// Adds a inlet to all faces



// Inlets
#define L_INLET_ON				// Turn on inlet boundary (assumed left-hand wall - default Do Nothing)
//#define L_INLET_REGULARISED		// Specify the inlet to be a regularised inlet condition (Latt & Chopard)
//#define L_INLET_NRBC			// Turn on NRBC at inlet


// Outlets
#define L_OUTLET_ON				// Turn on outlet boundary (assumed right-hand wall for now -- default First Order Extrap.)
//#define L_OUTLET_NRBC			// Turn on NRBC at outlet


// Periodicity
//#define L_PERIODIC_BOUNDARIES		// Turn on periodic boundary conditions (only applies to fluid-fluid interfaces)


// Solids
//#define L_WALLS_ON				// Turn on no-slip walls (default is top, bottom, front, back unless L_WALLS_ON_2D is used)
//#define L_WALLS_ON_2D			// Limit no-slip walls to top and bottom no-slip walls only
#define L_wall_thickness	1		// Thickness of walls in coarsest lattice units



/*
*******************************************************************************
********************************* Object Data *********************************
*******************************************************************************
*/

// Bounce-back solids
//#define L_SOLID_BLOCK_ON			// Turn on solid object (bounce-back) specified below

#ifdef L_SOLID_BLOCK_ON
	#define L_block_on_grid_lev 0		// Provide grid level on which block should be added 
	#define L_block_on_grid_reg 0		// Provide grid region on which block should be added 
	// Wall labelling routine implements this
	// Specified in lattice units (i.e. by index) local to the chosen grid level
	#define L_obj_x_min 90		// Index of start of object/wall in x-direction
	#define L_obj_x_max 110		// Index of end of object/wall in x-direction
	#define L_obj_y_min 20			// Index of start of object/wall in y-direction
	#define L_obj_y_max 40		// Index of end of object/wall in y-direction
	#define L_obj_z_min 65		// Index of start of object/wall in z-direction
	#define L_obj_z_max 85		// Index of end of object/wall in z-direction
#endif


// Bounce-back objects from point clouds
#define L_SOLID_FROM_FILE

#ifdef L_SOLID_FROM_FILE
	#define L_object_on_grid_lev 2		// Provide grid level on which object should be added 
	#define L_object_on_grid_reg 0		// Provide grid region on which object should be added
	// Following specified in lattice units (i.e. by index) local to the chosen grid level
	#define L_start_object_x 16
	#define L_start_object_y 16
	#define L_centre_object_z 80
	#define L_object_length 64				// The object input is scaled based on this dimension
	#define L_object_scale_direction eXDirection		// Scale in this direction (Specify as enumeration)
	#define L_object_length_ref 64			// Reference length to be used in the definition of Reynolds number
#endif


// BFL objects
//#define L_BFL_ON

#ifdef L_BFL_ON
	#define L_bfl_on_grid_lev 1		// Provide grid level on which BFL body should be added 
	#define L_bfl_on_grid_reg 0		// Provide grid region on which BFL body should be added
	// Following specified in lattice units (i.e. by index) local to the chosen grid level
	#define L_start_bfl_x 50
	#define L_start_bfl_y 100
	#define L_centre_bfl_z 20
	#define L_bfl_length_x 50			// The BFL object input is scaled based on this dimension
	#define L_bfl_scale_direction eXDirection	// Scale in this direction (Specify as enumeration)
	#define L_bfl_length_ref 10			// Reference length to be used in the definition of Reynolds number
#endif



/*
*******************************************************************************
****************************** Multi-grid Data ********************************
*******************************************************************************
*/

#define L_NumLev 2		// Levels of refinement
#define L_NumReg 1		// Number of refined regions (can be arbitrary if L_NumLev = 0)

#if L_NumLev != 0
// Global lattice indices (in terms of each grid level) for each refined region specified on each level


// Following options are only here to making testing different grid combinations easier
#if (L_NumReg == 2 && L_NumLev == 2) 
	const static int RefXstart[L_NumLev][L_NumReg]	= { {5, 5}, {2, 2} };
	const static int RefXend[L_NumLev][L_NumReg]	= { {25, 25}, {20, 10} };
	const static int RefYstart[L_NumLev][L_NumReg]	= { {5, 14}, {5, 2} };
	const static int RefYend[L_NumLev][L_NumReg]	= { {12, 25}, {10, 10} };
	// If doing 2D, these can be arbitrary values
	static int RefZstart[L_NumLev][L_NumReg]		= { {5, 10}, {2, 2} };
	static int RefZend[L_NumLev][L_NumReg]			= { {20, 15}, {10, 10} };

#elif (L_NumReg == 1 && L_NumLev == 1)
	const static int RefXstart[L_NumLev][L_NumReg]	= { 8 };
	const static int RefXend[L_NumLev][L_NumReg]	= { 30 };
	const static int RefYstart[L_NumLev][L_NumReg]	= { 11 };
	const static int RefYend[L_NumLev][L_NumReg]	= { 21 };
	// If doing 2D, these can be arbitrary values
	static int RefZstart[L_NumLev][L_NumReg]		= { 4 };
	static int RefZend[L_NumLev][L_NumReg]			= { 28 };

#elif (L_NumReg == 1 && L_NumLev == 2)
	const static int RefXstart[L_NumLev][L_NumReg]	= { {16}, {8} };
	const static int RefXend[L_NumLev][L_NumReg]	= { {60}, {80} };
	const static int RefYstart[L_NumLev][L_NumReg]	= { {22}, {8} };
	const static int RefYend[L_NumLev][L_NumReg]	= { {42}, {32} };
	// If doing 2D, these can be arbitrary values
	static int RefZstart[L_NumLev][L_NumReg]		= { {8}, {8} };
	static int RefZend[L_NumLev][L_NumReg]			= { {56}, {88} };

#elif (NumReg == 1 && NumLev == 3)
	const static size_t RefXstart[NumLev][NumReg]	= { {8},	{4},	{8} };
	const static size_t RefXend[NumLev][NumReg]		= { {34},	{48},	{80} };
	const static size_t RefYstart[NumLev][NumReg]	= { {9},	{4},	{8} };
	const static size_t RefYend[NumLev][NumReg]		= { {23},	{24},	{32} };
	// If doing 2D, these can be arbitrary values
	static size_t RefZstart[NumLev][NumReg]		= { {2},	{4},	{8} };
	static size_t RefZend[NumLev][NumReg]		= { {30},	{52},	{88} };

#elif (L_NumReg == 1 && L_NumLev == 3)
	const static int RefXstart[L_NumLev][L_NumReg]	= { {8},	{4},	{8} };
	const static int RefXend[L_NumLev][L_NumReg]	= { {34},	{48},	{80} };
	const static int RefYstart[L_NumLev][L_NumReg]	= { {9},	{4},	{8} };
	const static int RefYend[L_NumLev][L_NumReg]	= { {23},	{24},	{32} };
	// If doing 2D, these can be arbitrary values
	static int RefZstart[L_NumLev][L_NumReg]		= { {2},	{4},	{8} };
	static int RefZend[L_NumLev][L_NumReg]			= { {30},	{52},	{88} };

#elif (L_NumReg == 1 && L_NumLev == 4)
	const static int RefXstart[L_NumLev][L_NumReg]	= { {5},	{3},	{5},	{10} };
	const static int RefXend[L_NumLev][L_NumReg]	= { {25},	{35},	{55},	{80} };
	const static int RefYstart[L_NumLev][L_NumReg]	= { {0},	{0},	{0},	{0} };
	const static int RefYend[L_NumLev][L_NumReg]	= { {8},	{13},	{20},	{30} };
	// If doing 2D, these can be arbitrary values
	static int RefZstart[L_NumLev][L_NumReg]		= { {7},	{3},	{5},	{10} };
	static int RefZend[L_NumLev][L_NumReg]			= { {22},	{28},	{45},	{70} };

#endif

#endif


/*
*******************************************************************************
************************* Clean-up: NOT FOR EDITING ***************************
*******************************************************************************
*/

// Set dependent options
#if L_dims == 3
	#define L_nVels 27		// Use D3Q27

	#define L_MPI_dir 26	// 3D MPI configuration

#else
	#define L_nVels 9		// Use D2Q9

	// MPI config to 2D
	#define L_MPI_dir 8

	// Set Z limits for 2D
	#undef L_a_z
	#define L_a_z 0

	#undef L_b_z
	#define L_b_z 2

	#undef L_K
	#define L_K 1

	// Set object limits for 2D
	#undef L_obj_z_min
	#define L_obj_z_min 0

	#undef L_obj_z_max
	#define L_obj_z_max 0

	#undef L_ibb_d
	#define L_ibb_d 0

	// Set BFL start for 2D
	#undef L_centre_object_z
	#define L_centre_object_z 0

	// Set Object start for 2D
	#undef L_centre_bfl_z
	#define L_centre_bfl_z 0

	// Set IBB start for 2D
	#undef L_centre_ibb_z
	#define L_centre_ibb_z 0

	// Set z inlet velocity
	#undef L_u_0z
	#define L_u_0z 0

#endif

#if L_NumLev == 0
	// Set region info to default as no refinement
	const static int RefXstart[1][1]	= {0};
	const static int RefXend[1][1]		= {0};
	const static int RefYstart[1][1]	= {0};
	const static int RefYend[1][1]		= {0};
	static int RefZstart[1][1]			= {0};
	static int RefZend[1][1]			= {0};
#endif

// Clean up for using profiled inlet
#ifdef L_USE_INLET_PROFILE
	#undef L_u_0x
	#define L_u_0x ux_in[j]
	#undef L_u_0y
	#define L_u_0y uy_in[j]
	#undef L_u_0z
	#define L_u_0z uz_in[j]
#endif

#endif