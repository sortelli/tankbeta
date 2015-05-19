#ifndef tconst_h

#define XRES	  (63)	//screen is placed in blocks of ten pixles.  XRES and
#define YRES	  (47)   //YRES are how many rows an cols of blocks are used
#define WALL	  (BLACK)//
#define BULLET	  (6)    //colors of objects
#define FLOOR 	  (7)    //
#define TRNSPD	  (20)   //controls human delay for turning
#define N		  (0)    //
#define E		  (1)    //angles of tank rotation
#define S		  (2)    //
#define W		  (3)    //
#define BLNGTH	  (3)    //size of bullet
#define TLNGTH	  (10)	//size of tank
#define BMOVE	  (3)    //how many times faster a bullet moves than a tank
#define BRANGE	  (500)  //how far a bullet will travel
#define GAMELNTH (10)    //number of hits needed to win

struct point
{
	int x, y;
};


#define tconst_h
#endif

