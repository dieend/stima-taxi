/****************************************************************************
**    TEST FILE FOR graph (Dynamic Layout Alg)
**
**    HEADER   - DEFINITION OF CONSTANTS
**
** Author: dr. Szirmay-Kalos Laszlo (szirmay@fsz.bme.hu)
**	   Technical University of Budapest, Hungary
*****************************************************************************/
/*
*    DEFINITION OF OBJECT WINDOW PARAMETERS
*/
#define WINDOW_WIDTH 640.0
#define WINDOW_HEIGHT 480.0
#define OVERWINDOW_X		 WINDOW_WIDTH
#define OVERWINDOW_Y		 WINDOW_HEIGHT

#define WALL_MARGIN		 (OVERWINDOW_X / 10.0)

/*
*    MAXIMAL ALLOWABLE RELATION OF TWO NODES
*/
#define MAXRELATION		 10.0
/*
*    RETURN OF THE LAYOUT ALGORITHM
*/
#define STOPPED			 0
#define INSTABLE		 1
#define TOO_LONG		 2

/*
*   TYPE OF NODES
*/
#define MOVEABLE_NODE		 0
#define FIXED_NODE		 1

#define ALL_NODES		-1

/*
*   LOOK OF NODES
*/
#define NODESIZE_X		30
#define NODESIZE_Y		30

/*
*   MAXIMAL SIZE OF STRINGS
*/
#define MAXNAME			 10
#define MAXSTRING		 10

/*
*   RETURN OF SEARCH FUNCTIONS
*/
#define EMPTY_LIST		 0
#define FIRST_FOUND		 1
#define FOUND			 2
#define NOT_FOUND		 3
