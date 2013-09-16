/************************************************************************
**    TEST FILE FOR graph (Dynamic Layout Alg)
**
**    HEADER - GRAPH DATA STRUCTURE MANIPULATION
**
** Author: dr. Szirmay-Kalos Laszlo (szirmay@fsz.bme.hu)
**	   Technical University of Budapest, Hungary
*************************************************************************/
#pragma once
#include "defines.hpp"
#include <string>
#include "Point.hpp"
#include "Rectangle.hpp"
typedef char TYPE;

/************************************************************************/
class Node {
/************************************************************************/
    std::string   name;	// node name
    TYPE   type;		// fixed or movable
    Point pos;			// actual position
    Point speed;		// speed
    Point force;		// driving force to this node
public:
	   Node( std::string, TYPE );	     // constructor

    Point& Position( void )	     { return pos;	    }
    Point& Speed( void )	     { return speed;	    }
    Point& Force( void )	     { return force;	    }

    void   AddForce( Point f )     { force += f;	    }

    std::string  GetName( void )	     { return name;	    }
    TYPE   GetType( void )	     { return type;	    }
};

/************************************************************************/
class Relation {
/************************************************************************/
    char     name[MAXNAME + 1];	   // relation name
    double   intensity;		   // relation intensity
    Node   * relation_to;	   // related node
public:
	     Relation( std::string , Node *, double );
    void     SetRelation( std::string, double );
    std::string    GetName( void )		 { return name;		 }
    double   GetRelation( void )	 { return intensity;	 }
    Node *   GetOtherNode( void )	 { return relation_to;	 }

};

/************************************************************************/
class RelationElem : public Relation {
/************************************************************************/
    RelationElem  *    next_relation;		      // next on the list
public:
    RelationElem( std::string name, Node * p, double r );
    void	   SetNext( RelationElem * rn ) { next_relation = rn;	}
    RelationElem * GetNext( void )		{ return next_relation; }
};

/************************************************************************/
class NodeElem : public Node {
/************************************************************************/
    int		    ser_num;	    // serial number in list
    NodeElem	 *  next_node;	    // pointer to next node
    RelationElem *  relation;	    // first relation of this node
public:
		    NodeElem(std::string, TYPE);
    void	    SetNext( NodeElem *p )	    { next_node = p;	     }
    void	    SetRelation( RelationElem *p )  { relation = p;	     }
    void	    SetSerNum( int sernum )	    { ser_num = sernum;	     }
    NodeElem	 *  GetNext( void )		    { return next_node;	     }
    RelationElem *  GetRelation( void )		    { return relation;	     }
    int		    GetSerNum( void )		    { return ser_num;	     }
};


/************************************************************************/
class Graph {
/************************************************************************/
    int		   nfixnode;	     // number of fix nodes
    int		   nmovnode;	     // number of movable nodes
    NodeElem *	   currnode;	     // current node
    NodeElem *	   relatenode;	     // actual relation of curr
    NodeElem *	   start_node;	     // start of list
    NodeElem *	   last_node;	     // end of list
    RelationElem * currelation;	     // relation of nodes list
    RelationElem * prevrelation;     // previous to currelation

    void	 SwapRelation( void );	  // swap currnode and relatenode
					  // if currnode is further in the
					  // list
public:
		 Graph( void );

    void	 SetNodePos( Point );	  // sets position of currnode
    void	 SetRelation( double );	  // sets intensity of currelation
    NodeElem *	 GetNode( void )	  { return currnode;	       }
    NodeElem *	 GetRelateNode( void )	  { return relatenode;	       }
    double	 GetRelation( void );	  // get intensity of currelation
    std::string	 GetRelationName( void ); // get name of currelation
    bool	 AddNode( std::string, TYPE );  // add new node to the list
    void	 AddRelation( std::string, double ); // add new relation
    bool	 SearchNode( std::string );	  // search node by name
    bool	 RelSearchNode( std::string );
    int		 SearchRelation( void );  // search relation of currnode and relatenode

    bool	 SaveNodes( std::string );	  // save to a file
    void	 RestoreNodes( std::string );	  // restore from file

    int		 Placement( void );	  // place nodes step-by-step
    void	 RandomArrange( void );	  // arrange nodes randomly
    int		 DynamicLayout( int );	  // dynamic layout algorithm

    bool	 FirstNode( void );	  // select first node on the list
    bool	 FirstMoveNode( void );	  // select first moveable node
    bool	 NextNode( int max = ALL_NODES ); // select next to currnode
    bool	 FirstRelation( void );	  // select first relation of currnode
    bool	 NextRelation( void );	  // select next relation

};

/************************************************************************/
class ObjectSpace : public Graph {
/************************************************************************/
    double	     scale_x;		// scale of window->viewport transform
    double	     scale_y;
    Rectangle	     vwindow;	    // object space window
    Rectangle	     viewport;	    // viewport
    void	     SetScale( void );	// calculate scale from vwindow and viewport
public:
	   ObjectSpace( void );

    void   SetViewPort( Rectangle );

    Point  ScreenPos( NodeElem * );    // get screen coordinates of node
    Point  ScreenPos( Point );	       // window -> viewport transform
    Point  ScreenPos( void )	      { return ScreenPos( GetNode( ) );	   }
    Point  RelScreenPos( void )	      { return ScreenPos( GetRelateNode() );}
};
