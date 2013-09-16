#include "Graph.hpp"
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
    strcpy( name, nname );
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
Graph :: Graph()
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
void Graph :: RestoreNodes ( std::string file_name )
{
    // TODO
}

/*------------------  SaveNodes	  ----------------------------*/
/* Saves the node-relation data structure to a file name      */
/* The file type is TEXT.					*/
/* IN  : file name						*/
/*--------------------------------------------------------------*/
bool Graph :: SaveNodes ( std::string file_name )
{
    // TODO
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
bool Graph :: SearchNode ( std::string name )
{
    if ( !FirstNode() ) return false;
    do {
	if ( strcmp( currnode -> GetName(), name) == 0 ) return true;
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

/************************************************************************/
/*  OBJECT SPACE							*/
/************************************************************************/
/*----------------- ObjectSpace Constructor --------------------*/
/* Initializes object space window				*/
/* IN  : -							*/
/* OUT : -							*/
/*--------------------------------------------------------------*/
ObjectSpace :: ObjectSpace( )
	:vwindow( 0, 0, (double)OVERWINDOW_Y, (double)OVERWINDOW_X ),
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
