#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define N 4
#define NxN (N*N)
#define TRUE 1
#define FALSE 0


/*   THIS IS  A COMPLETE PROGRAM.    */


struct state {
	int tiles[N][N];
	int f, g, h;
	short zero_row, zero_column;	/* location (row and colum) of blank tile 0 */
	struct state *next;
	struct state *parent;			/* used to trace back the solution */
};

int goal_rows[NxN];
int goal_columns[NxN];
struct state *start,*goal;
struct state *fringe = NULL, *closed = NULL;
struct state *succ_states[4];

void print_a_state(struct state *pstate) {
	int i,j;
	for (i=0;i<N;i++) {
		for (j=0;j<N;j++) 
			printf("%2d ", pstate->tiles[i][j]);
		printf("\n");
	}
	printf("\n");
}

void initialize(char **argv){
	int i,j,k,index, tile;

	start=(struct state *) malloc(sizeof(struct state));
	index = 1;
	for (j=0;j<N;j++)
		for (k=0;k<N;k++) {
			tile=atoi(argv[index++]);
			start->tiles[j][k]=tile;
			if(tile==0) {
				start->zero_row=j;
				start->zero_column=k;
			}
		}
	start->f=0;
	start->g=0;
	start->h=0;
	start->next=NULL;
	start->parent=NULL;
	printf("initial state\n");
	print_a_state(start); //prints out the state

	goal=(struct state *) malloc(sizeof(struct state));
	goal_rows[0]=3;
	goal_columns[0]=3;

	for(index=1; index<NxN; index++){
		j=(index-1)/N;
		k=(index-1)%N;
		goal_rows[index]=j;
		goal_columns[index]=k;
		goal->tiles[j][k]=index;
	}
	goal->tiles[N-1][N-1]=0;	      /* empty tile=0 */
	goal->f=0;
	goal->g=0;
	goal->h=0;
	goal->next=NULL;
	printf("goal state\n");
	print_a_state(goal);

}

/* merge the remaining states pointed by succ_states[] into fringe. 
 * Insert states based on their f values --- keep f values sorted. */
void merge_to_fringe() { 
	for(int i = 0; i < N; i++){
        if(succ_states[i] == NULL){
            continue;
        }
        
        struct state *toInsert = (struct state *) malloc(sizeof(struct state));
		
        memcpy(toInsert->tiles, succ_states[i]->tiles, NxN*sizeof(int));
        toInsert->f = succ_states[i]->f;
        toInsert->g = succ_states[i]->g;
        toInsert->h = succ_states[i]->h;
        toInsert->zero_row = succ_states[i]->zero_row;
        toInsert->zero_column = succ_states[i]->zero_column;
        toInsert->parent = succ_states[i]->parent;

        if (fringe == NULL)
        {
            fringe = toInsert;
            continue;
        }

        struct state *temp = fringe;

        int hasInserted = FALSE;

        while(temp != NULL && temp->next != NULL){
            if(toInsert->f < temp->next->f){
                toInsert->next = temp->next;
                temp->next = toInsert;
                hasInserted = TRUE;
                break;
            }
        temp = temp->next;
        }

        
        if(hasInserted == FALSE){
            temp->next = toInsert;
        }

    }

}

/*swap two tiles in a state*/
void swap(int row1,int column1,int row2,int column2, struct state * pstate){
	int tile = pstate->tiles[row1][column1];
	pstate->tiles[row1][column1]=pstate->tiles[row2][column2];
	pstate->tiles[row2][column2]=tile;
}

//manhattan distance implementation
int manhattanDist(int entry, int row, int col){
	if(entry ==0){
		return 0;
	}
	for(int i=0; i < NxN; i++){
		for(int j=0; j<NxN; j++){
			if(goal->tiles[i][j] == entry){
				return abs(row - i) + abs(col-j);
			}
		}
	}
}

int max(int a, int b){
	if( a>b){
		return a;
	}

	else{
		return b;
	}
}

/*update the f,g,h function values for a state pointed by a pointer in succ_states */
void update_fgh(struct state* pstate) {
	//g is distance from the root
	if(pstate->parent != NULL){
		pstate->g = pstate->parent->g +1;
	}else{
		pstate->g=1;
	}

	//h is distance to the goal state
	int h1=0, h2=0;
	int i,j;
	int correct=0;
	//h1 is misplaced, h2 is how far from tile to the desired location
	for(i=0; i<NxN; i++){
		for(j=0; j<NxN; j++){
			correct++;
			if(pstate->tiles[j][i] != correct){
				h1++;
			}
			h2+= manhattanDist(pstate->tiles[j][i], j, i);
		}
	}
	pstate->h=max(h1,h2);
	//f = g + h
	pstate->f=pstate->g + pstate->h;
}

/* 0 goes down by a row */
void move_down(struct state * pstate){
	swap(pstate->zero_row, pstate->zero_column, pstate->zero_row+1, pstate->zero_column, pstate); 
	pstate->zero_row++;
}

/* 0 goes right by a column */
void move_right(struct state * pstate){
	swap(pstate->zero_row, pstate->zero_column, pstate->zero_row, pstate->zero_column+1, pstate); 
	pstate->zero_column++;
}

/* 0 goes up by a row */
void move_up(struct state * pstate){
	swap(pstate->zero_row, pstate->zero_column, pstate->zero_row-1, pstate->zero_column, pstate); 
	pstate->zero_row--;
}

/* 0 goes left by a column */
void move_left(struct state * pstate){
	swap(pstate->zero_row, pstate->zero_column, pstate->zero_row, pstate->zero_column-1, pstate); 
	pstate->zero_column--;
}

/* expand a state, and get its children states. Children states pointed by the pointers in succ_states.
 */
void expand(struct state *selected) {
	 for(int i = 0; i < N; i++){
        succ_states[i] = (struct state *) malloc(sizeof(struct state));
        memcpy(succ_states[i]->tiles, selected->tiles, NxN*sizeof(int));
        succ_states[i]->zero_row = selected->zero_row;
        succ_states[i]->zero_column = selected->zero_column;
        succ_states[i]->parent = selected;

    }

    move_down(succ_states[0]);
    move_right(succ_states[1]);
    move_up(succ_states[2]);
    move_left(succ_states[3]);

    for(int i = 0; i < N; i++){
        update_fgh(succ_states[i]);
    }

}

int states_same(struct state *a,struct state *b) {
	int flg=FALSE;
	if (memcmp(a->tiles, b->tiles, sizeof(int)*NxN) == 0)
		flg=TRUE;
	return flg;
}

/* Filtering:
 * check the state pointed by succ_states[i] to determine whether this state is repeating.
 * free the state if it is repeating. 
 */ 
void filter(int i, struct state *pstate_list){ 
	
	if(pstate_list == NULL || succ_states[i] == NULL){
        return;
    }
    struct state *temp = pstate_list;
    while(temp != NULL){
        if(states_same(succ_states[i], temp)){
            succ_states[i] = NULL;
            return;
        }
        temp = temp->next;
    }
}

int main(int argc,char **argv) {
	int iter,cnt;
	struct state *curr_state, *cp, *solution_path;
	int ret, i, pathlen=0, index[N-1];

	solution_path=NULL;
	initialize(argv);	/* init initial and goal states */
	fringe=start; 

	iter=0; 
	while (fringe!=NULL) {	
		curr_state=fringe;
		fringe=fringe->next;  /* get the first state from fringe to expand */
		

		

		if(states_same(curr_state,goal)){ /* a solution is found */
			do{ /* trace back and add the states on the path to a list */
				curr_state->next=solution_path;
				solution_path=curr_state;
				curr_state=curr_state->parent;
				pathlen++;
			} while(curr_state!=NULL);
			printf("Path (length=%d):\n", pathlen); 
			curr_state=solution_path;
			//... /* print out the states on the list */
			do{
                print_a_state(solution_path);
                solution_path = solution_path->next;
            }while(solution_path != NULL);

			break;
		}
		expand(curr_state);       /* generate new states */


		for(i=0;i<4;i++){
			filter(i,fringe); /* Check succ_states[i] agaist fringe to see if it is repeatng */
			filter(i,closed); /* Check succ_states[i] agaist closed to see if it is repeatng */
			
		}


		merge_to_fringe(); /* add new states to fringe */

		curr_state->next=closed;
		closed=curr_state;	
		iter++;
		if(iter++ %1000 == 0) printf("iter %d\n", iter);
	}
	return 0;
} /* end of main */
