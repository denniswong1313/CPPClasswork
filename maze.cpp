#include <iostream>
#include <string>
#include "grid.hh"
using namespace std;
using namespace gridlib; 

//Check if string contains only letters u,l,r,d,U,L,R,D
bool isCorrectLetter(char z) {
	if (z == 'u' || z == 'l'|| z == 'r'|| z == 'd'|| z == 'U'|| z == 'L'|| z == 'R'|| z == 'D')
		return true;
	else
		return false;
}

bool isPathWellFormed(string path) {

	if ( (path == ""))
			return false;

	for( int i = 0; i < path.size() - 2 ; i++) 
	{
		//Path contains only numbers 0-9 and letters u,l,r,d,U,L,R,D
		if( (path[i] >= '0' && path[i] <='9') || isCorrectLetter(path[i]))
			cout << "";
		else
			return false;
		
		//First entry in path is a number
		if( !(path[0] >= '0' && path[0] <= '9') )
			return false;

		//Last entry in path is direction
		if( !isCorrectLetter(path[path.size()-1]))
			return false;

		//Path does not have two letters in a row
		if( (isCorrectLetter (path[i])) && ( isCorrectLetter (path[i+1])))
			return false;

		//Path does not have 3 numbers in a row
		if( (path[i] >= '0' && path[i] <= '9') && (path[i+1] >= '0' && path[i+1] <= '9') && (path[i+2] >= '0' && path[i+2] <= '9'))
			return false;

		
	}

	 return true;
}

int traverseSegment(int r, int c, char dir, int maxSteps) {
	
	//Start space is not a wall.
	if (isWall(r, c))
		return -1;

	//maxSteps is not negative.
	if (maxSteps < 0)
		return -1;

	//Direction is valid
	if (!(isCorrectLetter(dir)))
		return -1;

	//Calculate max steps along segment.
	for (int i=0; i < maxSteps + 1; i++){
		if ((r == 0) || (c == 0))
			return i;

		if (dir == 'U' || dir == 'u')
		{
			r--; 
			if (r == 0)
				return i;
		}

		if (dir == 'D' || dir == 'd')
		{
			if (r == (getRows()))
				return i;
			r++;
		}

		if (dir == 'L' || dir == 'l')
		{
			c--;
			if (c == 0)
				return i;
			
		}

		if (dir == 'R' || dir == 'r')
		{
			if (c == (getCols()))
				return i;
			c++;
		}
		
		if (isWall(r,c))
				return i;
		if (i == maxSteps)
			return i;
}
}

int countBombsAlongSegment(int r, int c, char dir, int maxSteps) {

	int steps = traverseSegment(r, c, dir, maxSteps);

	if(steps == -1)
		return -1;
	
	int b = 0;

	for (int i=0; i < steps + 1; i++){

		if (dir == 'U' || dir == 'u')
		{
			if (isBomb(r,c))
				b++;
			r--;
		}
		if (dir == 'D' || dir == 'd')
		{
			if (isBomb(r,c))
				b++;
			r++;
		}

		if (dir == 'L' || dir == 'l')
		{
		
			if (isBomb(r,c))
				b++;
			c--;
		}

		if (dir == 'R' || dir == 'r')
		{
			if (isBomb(r,c))
				b++;
			c++;
		}
	}

	return b;
}

int bombKill(int r, int c, char dir, int maxSteps, unsigned int nlives) {
	
	for (int i=0; i < maxSteps + 1; i++) {

		if (dir == 'U' || dir == 'u')
		{
			if ((isBomb(r,c) && (--nlives == 0)))
			{
				return i;	
			}
			r--; 
		}

		if (dir == 'D' || dir == 'd')
		{
			if ((isBomb(r,c)) && (--nlives == 0))
			{
				return i;
			}
			r++;
		}

		if (dir == 'L' || dir == 'l')
		{
			if ((isBomb(r,c)) && (--nlives == 0))

				{
					return i;
				}
			c--;
		}

		if (dir == 'R' || dir == 'r')
		{
			if ((isBomb(r,c)) && (--nlives == 0))
			{
				{
					return i;
				}
			}
			c++;
		}		
}
}



int traversePath (int sr, int sc, int er, int ec, string path, unsigned int nlives, int& nsteps) {
	if (!(isPathWellFormed(path)))
		return -1; 

	if ((isWall(sr, sc)) || (isWall(er, ec)))
		return -1;

	for (int i=0; i < path.size() - 1; i++) {
		int maxSteps;

		if ((path[i] >= '0' && path[i] <= '9') && (isCorrectLetter(path[i+1])))
		{
			if (i != 0) {
				if ((path[i] >= '0' && path[i] <= '9') && (path[i-1] >= '0' && path[i-1] <= '9'))
				{
					maxSteps = (((path[i-1]-'0')*10) + (path[i]));
				}
				else 
				{
					maxSteps = (path[i] - '0');
				}
			}
			else 
			{
				maxSteps = (path[i] - '0');
			}
			

				if ((path[i+1] == 'U') || (path[i+1] == 'u'))
				{
					int moves = traverseSegment(sr, sc, path[i+1], maxSteps);
					int nBombs = countBombsAlongSegment(sr, sc, path[i+1], moves);
					if (nlives > nBombs)
					{
						nlives -= nBombs; 
						nsteps += moves;
					}
					else
					{
						nsteps += bombKill(sr, sc, path [i+1], moves, nlives);
						return 3;
					}

					if (maxSteps > moves)
					{ 
						return 2;
					}

					
					sr -= moves;
				}
				
				if ((path[i+1] == 'D') || (path[i+1] == 'd'))
				{
					int moves = traverseSegment(sr, sc, path[i+1], maxSteps);
					int nBombs = countBombsAlongSegment(sr, sc, path[i+1], moves);
					if (nlives > nBombs)
					{
						nlives -= nBombs; 
						nsteps += moves;
					}
					else
					{
						nsteps += bombKill(sr, sc, path [i+1], moves, nlives);
						return 3;
					}

			
					if (maxSteps > moves)
					{
						return 2;
					}
					sr += moves;
				}

				if ((path[i+1] == 'R') || (path[i+1] == 'r'))
				{
					int moves = traverseSegment(sr, sc, path[i+1], maxSteps);
						int nBombs = countBombsAlongSegment(sr, sc, path[i+1], moves);
					if (nlives > nBombs)
					{
						nlives -= nBombs; 
						nsteps += moves;
					}
					else
					{
						nsteps += bombKill(sr, sc, path [i+1], moves, nlives);
						return 3;
					}

					if (maxSteps > moves)
					{
						return 2;
					}
					sc += moves;
				}

				if ((path[i+1] == 'L') || (path[i+1] == 'l'))
				{
					int moves = traverseSegment(sr, sc, path[i+1], maxSteps);
						int nBombs = countBombsAlongSegment(sr, sc, path[i+1], moves);
					if (nlives > nBombs)
					{
						nlives -= nBombs; 
						nsteps += moves;
					}
					else
					{
						nsteps += bombKill(sr, sc, path [i+1], moves, nlives);
						return 3;
					}

					if (maxSteps > moves)
					{
						return 2;
					}
					sc -= moves;
				}
		}
	
	}

	if ((sr != er) || (sc != ec))
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}




	


int main ()
{
	string test = "2U1r01R0u2d1r"; 

	gridlib::setSize(3,4);      // make a 3 by 4 empty grid
	gridlib::setWall(1,4);      // put a wall at (1,4)
	gridlib::setWall(2,2);      // put a wall at (2,2)
	if (!gridlib::isWall(3,2))  // if there's no wall at (3,2)  [there isn't]
	    gridlib::setWall(3,2);  //    put a wall at (3,2)
	if (!gridlib::isBomb(1,3))  // if there's no bomb at (1,3)  [there isn't]
	    gridlib::setBomb(1,3);  //    put a bomb at (1,3)
	gridlib::draw(3,1, 3,4);    // draw the grid, showing an S at (3,1)
	                    //    start position, and an E at (3,4)

	int nsteps = 0;
	cout << traversePath(3, 1, 3, 4, "2u2r2d1r", 6, nsteps) << endl;
	cout << nsteps << endl;
	return 0;
	
}



