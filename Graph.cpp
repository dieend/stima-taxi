#include "Graph.hpp"


/*
*    CONSTANTS
*/
const double TIME_STEP = 0.1;	     // time step of diff equ

const double MAX_FORCE = 500.0;	     // force shows instability
const double MIN_FORCE = 2.0;	     // force cosidered as 0
const double MAX_TIME_SCALE = 10.0;  // scale of max time of solution

const double MINFRICTION = 0.6;	     // friction boundaries
const double MAXFRICTION = 0.9;
const double MINIINERTIA = 0.1;	     // inverse inertia boundaries
const double MAXIINERTIA = 0.4;

const double ZERO_DIST =	10.0;  // distance considered as 0
const double WALL_OUT_DRIVE =	80.0;  // forces of the wall
const double WALL_MARGIN_DRIVE = 1.0;

const double SCALECONSTRAINT = OVERWINDOW_X / 3.5 / MAXRELATION;
const double MINCONSTRAINT = OVERWINDOW_X / 7.0;     // minimal constraint
/************************************************************************/
/*    NODE								*/
/************************************************************************/
/*-------------------	node constructor      ------------------*/
/* Constructs node   object and initializes			*/
/* IN  : name and type (MOVEABLE or FIXED) of node		*/
/* OUT : -							*/
/*--------------------------------------------------------------*/
Node :: Node(std::string newname, TYPE ntype)
{
    name = newname;
    type  = ntype;
    force = Point(0.0, 0.0);
    pos	  = Point(0.0, 0.0);
    speed = Point(0.0, 0.0);
}


/************************************************************************/
/*    RELATION								*/
/************************************************************************/
/*------------------- relation constructor    ------------------*/
/* Constructs relation object and initializes			*/
/* IN  : name , related node, intensity,			*/
/*--------------------------------------------------------------*/
Relation :: Relation( std::string nname, Node * np, double r )
{
    SetRelation( nname, r );
    relation_to = np;
}

/*-------------------  SetRelation     -------------------------*/
/* Change the name intensity and relation of a constructed rel	*/
/* IN  : name, intensity					*/
/*--------------------------------------------------------------*/
void Relation :: SetRelation( std::string nname, double r )
{
    name = nname;
    intensity = r;
}

/************************************************************************/
/*    NODE ELEM								*/
/************************************************************************/
/*------------------- NodeElem	 constructor  ------------------*/
/* Constructs a node elem of a list object and initializes	*/
/* IN  : name and type (MOVEABLE or FIXED) of node		*/
/*--------------------------------------------------------------*/
NodeElem :: NodeElem( std::string name, TYPE type )
	  : Node( name, type )
{
    next_node = NULL;
    relation = NULL;
}


/************************************************************************/
/*    RELATION ELEM							*/
/************************************************************************/
/*------------------- RelationNode constructor	----------------*/
/* Constructs relation node of a list object and initializes	*/
/* IN  : name , related node, intensity,		       */
/*--------------------------------------------------------------*/
RelationElem :: RelationElem( std::string name, Node * p, double r )
	      : Relation( name, p, r )
{
    next_relation = NULL;
}

/************************************************************************/
/*    GRAPH = NODE - RELATION DATA					*/
/*									*/
/*    The Graph data structure is a dynamic structure.			*/
/*									*/
/*    The nodes are placed on a singly linked list, where fix nodes	*/
/*    are on the beginning, and moveable nodes are on the end.		*/
/*    The nodes are also identified by serial numbers, the moveable	*/
/*    nodes are having positive while fixed nodes negative numbers.	*/
/*    Control pointers : currnode - points to the actual node		*/
/*			 relatenode - other node which forms a pair	*/
/*					with currnode for relation ops	*/
/*			 start_node - the beginning of the list		*/
/*			 last_node - the end of the list		*/
/*									*/
/*    The relations of a given node are stored on an other linked list	*/
/*    connected to the node of the given node. The relation node	*/
/*    contains name, type, intensity parameters and a pointer to the	*/
/*    related node. The relation of two node is stored on the		*/
/*    relation list of the node having smaller serial number!		*/
/*    Control pointers : currelation -points to the actual relation node*/
/*			 prevrelation - points to the relation just	*/
/*			    before currelation on the actual relation	*/
/*			    list.					*/
/*									*/
/*  STRUCTURE OVERVIEW: P = Node, R = RelationNode			*/
/*									*/
/*  start_node				lastnode			*/
/*     P ---> P ---> P ---> P ---> P ---> P ---> NULL			*/
/*     |	     ^	    |	   ^	  ^				*/
/*     R ------------|	    R------|	  |				*/
/*     |		    |		  |				*/
/*    NULL		    R-------------|				*/
/*			    |						*/
/*			   NULL						*/
/************************************************************************/
/*------------------ Graph Constructor -------------------------*/
/* Initializes Graph data structure				*/
/*--------------------------------------------------------------*/
Graph :: Graph(Cities& cities):mCities(cities) 
{
    start_node = NULL;
    last_node  = NULL;
    currnode   = NULL;
    relatenode = NULL;
    currelation	 = NULL;
    prevrelation = NULL;
    nfixnode   = nmovnode = 0;
}

/*------------------ RestoreNodes ----------------------------*/
/* Restores the node-relation data structure from a file	*/
/* The file type is TEXT.					*/
/* IN  : file name						*/
/* SIDE EFFECT: - node-relation data structure is destroyed	*/
/*		  then it is restored from the given file	*/
/*--------------------------------------------------------------*/
void Graph :: RestoreNodes (const std::string& file_name )
{
	std::ifstream input;
	input.open(file_name);
	int n;
	input >> n;
	std::cout << n;
	std::string kota[100];
	for (int i=0; i<n; i++) {
		double x = (OVERWINDOW_X - WALL_MARGIN * 2.0) /
					(double)RAND_MAX * (double)rand() + WALL_MARGIN;

		double y = (OVERWINDOW_Y - WALL_MARGIN * 2.0) /
					(double)RAND_MAX * (double)rand() + WALL_MARGIN;
		input >> kota[i];
		mCities.addCity(kota[i]);
		AddNode(kota[i], MOVEABLE_NODE);
		currnode->SetPosition(Point(x,y));
	}
	for (int i=0; i<n; i++) {
		SearchNode(kota[i]) ;
		for (int j=0; j<n; j++) {
			double distance;
			input >> distance;
			if ((i!=j) && (distance != -1)) {
				NodeElem * tmpnode = currnode;
				RelSearchNode( kota[j] );
				char numstr[21]; // enough to hold all numbers up to 64-bits
				std::string rel_name = "";
				rel_name = rel_name + _itoa(i, numstr, 10) ;
				rel_name = rel_name + " ";
				rel_name = rel_name + _itoa(j, numstr, 10) ;
				AddRelation(rel_name , distance);
				mCities.addRoad(i,j,distance);
				currnode = tmpnode;
			}
		}
	}
	
	input.close();
}

/*------------------  SaveNodes	  ----------------------------*/
/* Saves the node-relation data structure to a file name      */
/* The file type is TEXT.					*/
/* IN  : file name						*/
/*--------------------------------------------------------------*/
bool Graph :: SaveNodes ( std::string file_name )
{
	//TODO
    return false;
}


/*-------------------	  SetNodePos	  --------------------*/
/* Sets the position of a node				      */
/* IN  : new position						*/
/*--------------------------------------------------------------*/
void Graph :: SetNodePos ( Point p )
{
    if ( currnode != NULL ) currnode -> Position( ) = p;
}

/*------------------------ GetRelation	 -----------------------*/
/* Gets the relation intensity of the actual relation		*/
/* IN  : -							*/
/* OUT : intensity ( -MAXRELATION -> MAXRELATION )		*/
/*--------------------------------------------------------------*/
double Graph :: GetRelation( )
{
    if (currelation != NULL) return currelation -> GetRelation( );
    else		     return 0.0;
}

/*------------------------ GetRelationName ---------------------*/
/* Gets the name of the actual relation				*/
/* OUT : name of NULL if no relation				*/
/*--------------------------------------------------------------*/
std::string Graph :: GetRelationName( )
{
    if ( currelation != NULL ) return currelation -> GetName( );
    else		       return NULL;
}

/*------------------------   AddNode   -----------------------*/
/* Checks if a node having the same name exist and if not new */
/* node is allocated and added to the beginning of the list if*/
/* the node is FIXED or to the end if it is MOVEABLE	      */
/* IN  : name and type of the new node			      */
/* OUT : is this name unique ?				      */
/* SIDE EFFECT: currnode is set to the new node.	      */
/*		if FIXED node				      */
/*		  start_node adjusted, nfixnode incremented   */
/*		if MOVEABLE NODE			      */
/*		  last_node adjusted, nmovnode incremented    */
/*------------------------------------------------------------*/
bool Graph :: AddNode ( std::string name, char type )
{
/*
*    DECIDE IF THIS NAME IS UNIQUE, IF NOT RETURN ERROR
*/
    if ( SearchNode( name ) ) return false;

    currnode = new NodeElem(name, type);

    if (start_node == NULL) {
/*
*    IF THIS IS THE FIRST NODE
*/
	start_node = last_node = currnode;
    } else {
	if ( type == FIXED_NODE ) {
/*
*    IF FIXED NODE -> ADD TO THE BEGINNING OF THE LIST
*/
	    currnode -> SetNext( start_node );
	    start_node = currnode;
	} else {
/*
*    IF MOVEABLE NODE -> ADD TO THE END OF THE LIST
*/
	    last_node -> SetNext( currnode );
	    last_node = currnode;
	}
    }
    if ( type == FIXED_NODE ) {
	nfixnode++;
	currnode -> SetSerNum( -nfixnode );
    } else {
	nmovnode++;
	currnode -> SetSerNum( nmovnode );
    }
    return true;
}

/*------------------------  SearchNode	  --------------------*/
/* Searches node by name				      */
/* IN  : searched name					      */
/* OUT : is there node having this name ?		      */
/* SIDE EFFECT: currnode is set to the found node.	      */
/*------------------------------------------------------------*/
bool Graph :: SearchNode (const std::string& name )
{
    if ( !FirstNode() ) return false;
    do {
	if ( currnode -> GetName() == name ) return true;
    } while ( NextNode () );

    return false;
}

/*------------------------  RelSearchNode --------------------*/
/* Searches relate node by name				      */
/* IN  : picked position					*/
/* OUT : is there node in the pick aperture ?		      */
/* SIDE EFFECT:							*/
/*  To ensure that relatenode has greater serial number than  */
/*  currnode:						      */
/*     IF found node has smaller serial number than currnode*/
/*	      relatenode is set to currnode		    */
/*	      currnode is set to the found node		    */
/*     ELSE							*/
/*	      relatenode is set to the found node.	    */
/*  Initializes currelation to the relation of currnode and   */
/*  relatenode.						      */
/*--------------------------------------------------------------*/
bool Graph :: RelSearchNode ( std::string name )
{
    NodeElem * oldcurrnode = currnode;
    bool       found	   = SearchNode( name );

    if ( found ) {
	relatenode = currnode;
	currnode = oldcurrnode;
	SwapRelation( );
	SearchRelation( );
    } else {
	currelation = NULL;
	currnode = oldcurrnode;
    }
    return found;
}

/*------------------ SearchRelation ----------------------------*/
/* Search for a relation between currnode and relatenode.   */
/* If this relation doesnot exist currelation is NULL and	*/
/* prevrelation points to the end of the relation list of	*/
/* currnode.						      */
/* IN  : -							*/
/* OUT : EMPTY_LIST  - No relation list				*/
/*	   FIRST_FOUND - The first relation node found		*/
/*	   FOUND	 - Not the first node found		*/
/*	   NOT_FOUND	 - No such relation			*/
/* SIDE EFFECT: currelation= searched relation or NULL		*/
/*		prevrelation= the previous relation or the last */
/*			      node of the relation list or NULL */
/*			      if no node at all			*/
/*--------------------------------------------------------------*/
int Graph :: SearchRelation ( )
{
    currelation = currnode -> GetRelation( );
    prevrelation = currnode -> GetRelation( );
    if (currelation == NULL) return EMPTY_LIST;
    if (currelation -> GetOtherNode() == relatenode) return FIRST_FOUND;

    currelation = prevrelation -> GetNext();

    for ( ; ; ) {
	if (currelation == NULL)			 return NOT_FOUND;
	if (currelation -> GetOtherNode() == relatenode) return FOUND;
	prevrelation = currelation;
	currelation = prevrelation -> GetNext();
    }
}

/*------------------------  SwapRelation    --------------------*/
/*  To ensure that relatenode has greater serial number than  */
/*  currnode:						      */
/*	IF relatenode node has smaller serial number than   */
/*	relatenode and currnode are swapped		    */
/* IN  : -							*/
/* OUT : -							*/
/*--------------------------------------------------------------*/
void Graph :: SwapRelation ( )
{
    NodeElem * tmpnode;

    if ( currnode == NULL || relatenode == NULL ) return;

    if ( currnode -> GetSerNum() > relatenode -> GetSerNum() ) {
	tmpnode = currnode;
	currnode = relatenode;
	relatenode = tmpnode;
    }
}

/*--------------------- AddRelation ----------------------------*/
/* Adds new or changes the parameters of an existing relation.	*/
/* If this is a new relation RelationNode is allocated and	*/
/* placed on the end of relation list of currnode.	      */
/* The parameters are set according to the explicit parameters	*/
/*  and the implicit relatenode par.			      */
/* IN  : name,intensity, type					*/
/* OUT : -							*/
/* SIDE EFFECT: currelation= new or changed relation		*/
/*--------------------------------------------------------------*/
void Graph :: AddRelation ( std::string name, double rel )
{
/*
*    CHECK IF THIS RELATION EXISTS OR FIND THE END OF RELATION LIST
*/
    switch ( SearchRelation( ) ) {

    case FIRST_FOUND:	     //	   THIS RELATION HAS BEEN ALREADY DEFINED
    case FOUND :
	currelation -> SetRelation( name, rel );
	return;

    case NOT_FOUND:	       //    NOT FIRST ADD NEW RELATION TO THE END OF LIST
	currelation = new RelationElem ( name, relatenode, rel );
	prevrelation -> SetNext ( currelation );
	return;

    case EMPTY_LIST:	    //	   THIS IS GOING TO BE THE FIRST
	currelation = new RelationElem ( name, relatenode, rel );
	currnode -> SetRelation( currelation );
	return;
    }
}

/*--------------------- FirstNode ----------------------------*/
/* Select currnode as start_node (beginning of the list	    */
/* IN  : -							*/
/* OUT : Are nodes on the list				      */
/*--------------------------------------------------------------*/
bool Graph :: FirstNode ( )
{
    if ( (currnode = start_node) == NULL ) return false;
    else				   return true;
}

/*--------------------- FirstMoveNode --------------------------*/
/* Select currnode as first moveable node on the list	    */
/* IN  : -							*/
/* OUT : Are moveable nodes on the list			      */
/*--------------------------------------------------------------*/
bool Graph :: FirstMoveNode ( )
{
    if ( (currnode = start_node) == NULL ) return false;

    while ( currnode -> GetType() != MOVEABLE_NODE ) {
	currnode = currnode -> GetNext();
	if ( currnode == NULL ) return false;
    }
    return true;
}

/*---------------------	 NextNode ----------------------------*/
/* Let currnode be the next after currnode		      */
/* IN  : maximal serial number to be considered of ALL_NODES  */
/* OUT : Was it the last node?				      */
/* SIDE EFFECT: currnode = NULL if no more nodes	      */
/*------------------------------------------------------------*/
bool Graph :: NextNode ( int maxsernum )
{
    if ( maxsernum == ALL_NODES ) {
	if (( currnode = currnode -> GetNext() ) == NULL ) return false;
    } else {
	if (( currnode = currnode -> GetNext() ) == NULL ||
	      currnode -> GetSerNum() > maxsernum ) return false;
    }
    return true ;
}

/*---------------------	 FirstRelation	------------------------*/
/* Select currrelation as first relation of the relation list	*/
/* of currnode.						      */
/* IN  : -							*/
/* OUT : Has the currnode any relation?			      */
/*--------------------------------------------------------------*/
bool Graph :: FirstRelation ( )
{
    if ( (currelation = currnode -> GetRelation()) == NULL ) {
		relatenode = NULL;
		return false;
    } else {
		relatenode = (NodeElem *)( currelation -> GetOtherNode() );
		return true;
    }
}

/*---------------------	 NextRelation --------------------------*/
/* Let currelation the next after currelation			*/
/* IN  : -							*/
/* OUT : Was it the last relation of the list?			*/
/*--------------------------------------------------------------*/
bool Graph :: NextRelation ( )
{
    if ( (currelation = currelation -> GetNext()) == NULL ) {
	relatenode = NULL;
	return false;
    } else {
	relatenode = (NodeElem *)( currelation -> GetOtherNode() );
	return true;
    }
}

/*------------------   RandomArrange ---------------------------*/
/* Random arrangement of nodes					*/
/*--------------------------------------------------------------*/
void Graph :: RandomArrange( )
{
/*
*    SKIP FIXED NODES
*/
    if ( !FirstMoveNode() ) return;
/*
*     MAIN CYCLE OF PLACING MOVEABLE NODES RANDOMLY
*/
    do {
	currnode -> Position( ) = Point((OVERWINDOW_X - WALL_MARGIN * 2.0) /
					 (double)RAND_MAX * (double)rand() + WALL_MARGIN,
					 (OVERWINDOW_Y - WALL_MARGIN * 2.0) /
					 (double)RAND_MAX * (double)rand() + WALL_MARGIN );
    } while ( NextNode() );
}

/****************************************************************************/
/* DYNAMIC LAYOUT base on MECHANICAL SYSTEM ANALOGY			    */
/* IN  : The serial number of the maximal moveable node to be considered    */
/* OUT : STOPPED  = All objects stopped					    */
/*	 INSTABLE = Instable, force goes to infinity			    */
/*	 TOO_LONG = Too much time elapsed				    */
/****************************************************************************/
int Graph :: DynamicLayout( int maxsernum )
/*--------------------------------------------------------------------------*/
{
/*
*    LOCALS
*/
    double constraint, friction, iinertia, dist;
    Point drive;			// drive forces
    Point direction;			// direction of drives
    double MAX_TIME = MAX_TIME_SCALE * (nmovnode + nfixnode + 1);
/*
*    INIT SPEED OF MOVEABLE NODES TO 0
*/
    if ( !FirstMoveNode() ) return STOPPED;
    do	currnode -> Speed( ) = Point(0.0, 0.0); while ( NextNode( maxsernum ) );
/*
*    MAIN CYCLE OF TIME IN THE SOLUTION OF DIFF EQUATION
*/
    for ( double t = 0.0 ; t < MAX_TIME ; t += TIME_STEP ) {
/*
*    INITIALIZE FORCE IN NODES TO 0
*/
	FirstNode();
	do currnode -> Force( ) = Point( 0.0, 0.0 ); while ( NextNode( maxsernum ) );
/*
*    CALCULATE FRICTION AND RESPONSE VALUES FROM t
*/
	friction = MINFRICTION + (MAXFRICTION - MINFRICTION) * t / MAX_TIME;
	iinertia = MAXIINERTIA - (MAXIINERTIA - MINIINERTIA) * t / MAX_TIME;
/*
*     CALCULATE DRIVE FORCE BETWEEN EACH PAIR OF NODES
*/
	FirstNode();
	do {
	  relatenode = currnode -> GetNext();
	  while ( relatenode != NULL && relatenode -> GetSerNum() <= maxsernum ) {

	    direction = currnode -> Position( ) - relatenode -> Position( );
	    dist  = direction.Size();
	    if ( dist < ZERO_DIST ) dist = ZERO_DIST;
/*
*    CALCULATE FORCE FROM THEIR RELATION
*/
	    switch( SearchRelation() ) {
	    case EMPTY_LIST:
	    case NOT_FOUND:
		constraint = MINCONSTRAINT + MAXRELATION * SCALECONSTRAINT;
		break;
	    case FOUND:
	    case FIRST_FOUND:
		constraint = MINCONSTRAINT + (MAXRELATION - currelation->GetRelation()) * SCALECONSTRAINT;
		break;
	    }
	    //	SET FORCE
	    drive = (constraint - dist) / dist * direction;
	    drive /= (double)(maxsernum + nfixnode);
	    currnode -> AddForce(drive);
	    relatenode -> AddForce(-drive);

	    relatenode = relatenode -> GetNext();
	  }
	} while ( NextNode( maxsernum ) );
/*
*    ADD ADDITIONAL FORCES AND DETERMINE MAXIMAL FORCE
*/
	double max_force = 0.0;

	FirstMoveNode();
	do {
/*
*   CALCULATE DRIVE FORCE OF BOUNDARIES AND ADD TO RELATION FORCES
*/
	   dist = currnode -> Position().X();
	   /*
	   *	FORCE OF LEFT WALL
	   */
	   if (dist < 0) {	      // OUT LEFT
	     drive = Point( -dist * WALL_OUT_DRIVE + WALL_MARGIN * WALL_MARGIN_DRIVE, 0.0 );
	     currnode -> AddForce(drive);
	   } else if (dist < WALL_MARGIN) {    // IN LEFT MARGIN
	     drive = Point((WALL_MARGIN - dist) * WALL_MARGIN_DRIVE, 0.0);
	     currnode -> AddForce(drive);
	   }
	   /*
	   *	FORCE OF THE RIGHT WALL
	   */
	   dist = currnode -> Position().X() - OVERWINDOW_X;

	   if (dist > 0) {	      // OUT RIGHT
	     drive = Point( -dist * WALL_OUT_DRIVE + WALL_MARGIN * WALL_MARGIN_DRIVE, 0.0);
	     currnode -> AddForce(drive);
	   } else if (-dist < WALL_MARGIN) {	// IN RIGHT MARGIN
	     drive = Point((-WALL_MARGIN - dist) * WALL_MARGIN_DRIVE, 0.0);
	     currnode -> AddForce(drive);
	   }

	   dist = currnode -> Position().Y();
	   /*
	   *	FORCE OF BOTTOM WALL
	   */
	   if (dist < 0) {	      // OUT BOTTOM
	     drive = Point(0.0, -dist * WALL_OUT_DRIVE + WALL_MARGIN * WALL_MARGIN_DRIVE );
	     currnode -> AddForce(drive);
	   } else if (dist < WALL_MARGIN) {    // IN BOTTOM MARGIN
	     drive = Point(0.0, (WALL_MARGIN - dist) * WALL_MARGIN_DRIVE);
	     currnode -> AddForce(drive);
	   }
	   /*
	   *	FORCE OF THE TOP WALL
	   */
	   dist = currnode -> Position().Y() - OVERWINDOW_Y;

	   if (dist > 0) {				      // OUT TOP
	     drive = Point( 0.0, -dist * WALL_OUT_DRIVE + WALL_MARGIN * WALL_MARGIN_DRIVE );
	     currnode -> AddForce(drive);
	   } else if (-dist < WALL_MARGIN) {		    // IN TOP MARGIN
	     drive = Point(0.0, (-WALL_MARGIN - dist) * WALL_MARGIN_DRIVE);
	     currnode -> AddForce(drive);
	   }
/*
*    MOVE NODE BY FORCE
*/
	    Point old_speed = currnode -> Speed( );
	    currnode -> Speed( ) = (1.0 - friction) * old_speed + iinertia * currnode -> Force( );
	    currnode -> Position( ) += 0.5 * (old_speed + currnode -> Speed( ) );

/*
*    CALCULATE MAXIMUM FORCE
*/
	    double abs_force = currnode -> Force().Size( );
	    if ( abs_force > max_force) max_force = abs_force;

	} while ( NextNode( maxsernum ) );
/*
*    STOP CALCULATION IF
*/
	if ( max_force < MIN_FORCE ) return STOPPED;  // All objects stopped
	if ( max_force > MAX_FORCE ) return INSTABLE; // Instable, force goes to infinity
    }
    return TOO_LONG; // Too much time elapsed
}


/************************************************************************/
/*    INITIAL PLACEMENT ALGORITHM					*/
/* OUT : STOPPED  = All objects stopped					*/
/*	 INSTABLE = Instable, force goes to infinity			*/
/*	 TOO_LONG = Too much time elapsed				*/
/************************************************************************/
int Graph :: Placement( )
/*----------------------------------------------------------------------*/
{
    Point	candidate;		// candidate position
    Point	relate_cent;		// center related objects
    Point	notrel_cent;		// center of related object
    Point	center( OVERWINDOW_X / 2, OVERWINDOW_Y / 2 );
    int		nrel;			// number of related objects
    int		nnotrel;		// displayed nodes
    double	perturb_x = OVERWINDOW_X / (double)RAND_MAX ;
    double	perturb_y = OVERWINDOW_Y / (double)RAND_MAX ;

/*
*    SKIP FIXED NODES
*/
    if ( !FirstMoveNode() ) return STOPPED;
/*
*     MAIN CYCLE OF INTRODUCING MOVABLE NODES STEP-BY-STEP
*/
    for( int inode = 1; ; inode++ ) {
/*
*    CALCULATE THE CENTER OF GRAVITY OF ALREADY INTRODUCED NODES
*    relate_cent IS FOR RELATED NODES
*    notrel_cent IS FOR NON_RELATED NODES
*/
	relate_cent = Point(0.0, 0.0);
	notrel_cent = Point(0.0, 0.0);
	nrel = 0;
	nnotrel = 0;		    // displayed nodes
	relatenode = currnode;

	for( FirstNode(); currnode != relatenode; NextNode() ) {
	    switch ( SearchRelation() ) {
	    case EMPTY_LIST:
	    case NOT_FOUND:
		    notrel_cent += currnode -> Position();
		    nnotrel++;
		    break;
	    case FIRST_FOUND:
	    case FOUND:
		    relate_cent += currnode -> Position();
		    nrel++;
		    break;
	    }
	}
	if ( nrel != 0 )       relate_cent /= (double)nrel;
	if ( nnotrel != 0 )    notrel_cent /= (double)nnotrel;
/*
*    IF THIS IS THE FIRST POINT -> PUT TO THE MIDDLE
*/
	if (nrel == 0 && nnotrel == 0) candidate = center;
	else
/*
*    IF NO NOT_RELATED NODE -> PUT TO THE CENTRE OF GRAVITY OF RELATED NODES
*/
	if ( nnotrel == 0 ) candidate = relate_cent;
	else
/*
*    IF NO RELATED NODE -> PUT TO THE MIRROR OF THE nrel_cent ON THE CENTRE
*/
	if ( nrel == 0 )  candidate = 2.0 * center - notrel_cent;
	else
/*
*    BOTH TYPE OF NODES EXIST ->
*    CALCULATE THE CANDIDATE POINT AS THE HALF MIRROR OF notrel_cent TO relate_cent
*/
	    candidate = 2.0 * relate_cent - 1.0 * notrel_cent;
/*
*    PERTURBATE RANDOMLY
*/
	candidate += Point( perturb_x / (double)(nfixnode + inode + 5) *
			     (double)( rand() - RAND_MAX / 2),
			     perturb_y / (double)(nfixnode + inode + 5) *
			     (double)( rand() - RAND_MAX / 2 ));
/*
*    DECIDE IF IT IS OUTSIDE -> FIND THE NEAREST INSIDE POINT
*/
	if ( candidate.X() < WALL_MARGIN)
	    candidate = Point( 2.0 * WALL_MARGIN, candidate.Y() );
	if ( candidate.X() > OVERWINDOW_X - WALL_MARGIN)
	    candidate = Point(OVERWINDOW_X - 2.0 * WALL_MARGIN, candidate.Y());

	if ( candidate.Y() < WALL_MARGIN)
	    candidate = Point( candidate.X(), 2.0 * WALL_MARGIN );
	if ( candidate.Y() > OVERWINDOW_Y - WALL_MARGIN)
	    candidate = Point(candidate.X(), OVERWINDOW_Y - 2.0 * WALL_MARGIN );

/*
*    SET POSITION OF THE NEW NODE
*/
	relatenode -> Position( ) = candidate;
/*
*    ARRANGE ALREADY DEFINED NODES BY DYNAMIC LAYOUT -> IGNORE EDGE CONSTRAINTS
*/
	NodeElem * oldcurrnode = currnode;
	char ret = DynamicLayout( inode );
	currnode = oldcurrnode;

	if ( ret != STOPPED || !NextNode() ) return ret;
    }
}
/*  OBJECT SPACE							*/
/************************************************************************/
/*----------------- ObjectSpace Constructor --------------------*/
/* Initializes object space window				*/
/* IN  : -							*/
/* OUT : -							*/
/*--------------------------------------------------------------*/
ObjectSpace :: ObjectSpace(Cities& cities )
	:Graph(cities), vwindow( 0, 0, (double)OVERWINDOW_Y, (double)OVERWINDOW_X ),
	 viewport( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT )
{
}

/*------------------------ SetScale ----------------------------*/
/* Initializes window -> viewport transform			*/
/* IN  : -							*/
/* OUT : -							*/
/*--------------------------------------------------------------*/
void ObjectSpace :: SetScale()
{
    scale_x = (double)viewport.Width() / (double)vwindow.Width();
    scale_y = (double)viewport.Height() / (double)vwindow.Height();
}


/*--------------------- SetViewPort ----------------------------*/
/* Sets viewport (Canvas RectAngle)				*/
/* IN  : new viewport						*/
/* OUT : -							*/
/* SIDE EFFECT: Recalculates window->viewport transform		*/
/*--------------------------------------------------------------*/
void ObjectSpace :: SetViewPort( Rectangle v )
{
    viewport = v;
    SetScale();
}


/*--------------------- ScreenPos ------------------------------*/
/* Transform a point from object space to screen space		*/
/* IN  : object space position					*/
/* OUT : screen space coordinates of point			*/
/*--------------------------------------------------------------*/
Point ObjectSpace :: ScreenPos( Point p )
{
    double x = (double)((p.X()-(double)vwindow.HorPos()) * scale_x);
    double y = (double)((p.Y()-(double)vwindow.VerPos()) * scale_y);
    return Point(x,y);
}

/*--------------------- ScreenPos ------------------------------*/
/* Gets the position of a NODE in screen coordinate system	*/
/* IN  : pointer to the NODE					*/
/* OUT : screen space coordinates of NODE position		*/
/*--------------------------------------------------------------*/
Point ObjectSpace :: ScreenPos( NodeElem * pnode )
{
    return ScreenPos( pnode -> Position() );
}

void ObjectSpace :: Draw(sf::RenderWindow& canvas)
{
	if ( !FirstNode() ) return;
    do {
	if ( FirstRelation() ) {
	    do ShowRelation(canvas); while ( NextRelation() );
	}
    } while ( NextNode() );


    if ( !FirstNode() ) return;
    do ShowNode(canvas); while ( NextNode() );

}
void Graph :: Convert(void) {
	if ( !FirstNode() ) return;
	do mCities.setCityPosition(currnode->GetName(), currnode->Position().X(), currnode->Position().Y()); while ( NextNode() );
}
void ObjectSpace :: ShowRelation(sf::RenderWindow& canvas){
	std::cout << currnode->Position().X() << "," << currnode->Position().Y() << " " << relatenode->Position().X() << "," << relatenode->Position().Y() << std::endl;
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(currnode->Position().X(),currnode->Position().Y())),
		sf::Vertex(sf::Vector2f(relatenode->Position().X(),relatenode->Position().Y()))
	};
	line[0].color =  sf::Color::Red;
	line[1].color =  sf::Color::Red;
	
	canvas.draw(line, 2, sf::Lines);
}
void ObjectSpace :: ShowNode(sf::RenderWindow& canvas){
	sf::RectangleShape node(sf::Vector2f(NODESIZE_X, NODESIZE_Y));
	node.setPosition(currnode->Position().X() - NODESIZE_X / 2, currnode->Position().Y() - NODESIZE_Y / 2);
	node.setFillColor(sf::Color::White);
	canvas.draw(node);
}
