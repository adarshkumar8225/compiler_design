/*Example grammar :
 A->vL
 L->a
 */

#include<stdio.h> 

#include<ctype.h> 
#include<string.h> 

//Function to calculate First Set.

void first_set(char, int , int);
  
// Functions to calculate Follow set 
void followfirst(char, int, int); 
void follow(char c); 
  

  
int count, n = 0; 
  
// Stores the final result of the First Sets 
char calc_first[10][100]; 
  
// Stores the final result of the Follow Sets 
char calc_follow[10][100]; 
int m = 0; 
  
// Stores the production rules 
char production[10][10]; 
char f[10], first[10]; 
int k,x=1; 
char ck; 
int e; 
char FIRST[10][10];//contains first set 
char Table[5][5];// the parsing table.
char terminal[5];//list of terminals used in grammar.

//function to create parse table.

void Parse_tab()
{

	Table[0][x]='$';
	int z,j;
        for( z=0;z<3;z++)
	{

	      if(z==0) printf("	");
	      else if(z>0) printf("%c	",FIRST[z-1][0]); 
              for( j=1;j<4;j++)
	      {
		      if(z==0) printf("%c	",Table[z][j]);
		      
		      else  if(Table[0][j]==FIRST[z-1][1]){
			      printf("%s ",production[z-1]);
			      break;
		        }
                      else  if(Table[0][j]==FIRST[z-1][2]){
                              printf("%s ",production[z-1]);
                              break;
                      }

		      else printf("	");
	      }
	      printf("\n");
	}
}

int main() 
{ 
    int jm = 0; 
    int km = 0; 
    int i, choice; 
    char c, ch; 
    count = 2; 
       
    strcpy(production[0], "A=vL");//production of grammar. 
    strcpy(production[1], "L=a"); 
 
    int kay; 
    char done[count];//list the non-term whose first set is calculated. 
    int ptr = -1; 
       
    int point1 = 0, point2, xxx; 
      
    for(k = 0; k < count; k++) //LHS of production. 
    { 
        c = production[k][0];	
        point2 = 0; 
        xxx = 0; 
        for(kay = 0; kay <= ptr; kay++) 
            if(c == done[kay])//check if First set for c is already calculated. 
                xxx = 1; 
                  
        if (xxx == 1) 
            continue; 
              
        first_set(c, 0, 0);//function call for first set calc. 
        ptr += 1; 
        done[ptr] = c;//Add c to calculated list. 
        printf("\n FIRST (%c) : { ", c);
        FIRST[k][0]=c;	
        calc_first[point1][point2++] = c; 
          
        // Printing the First Sets of the grammar 
        for(i = 0 + jm; i < n; i++) { 
            int lk = 0, chk = 0; 
              
            for(lk = 0; lk < point2; lk++) { 
                  
                if (first[i] == calc_first[point1][lk]) 
                { 
                    chk = 1; 
                    break; 
                } 
            } 
            if(chk == 0) 
            { 
                printf("%c, ", first[i]);
	        FIRST[k][i+1]=first[i];	
                calc_first[point1][point2++] = first[i]; 
            } 
        } 
        printf("}\n"); 
        jm = n; 
        point1++; 
    } 
    printf("\n"); 
  
    char donee[count]; //list the terminal whose follow set calculated.
    ptr = -1;  
    point1 = 0; 
    int land = 0; 
    for(e = 0; e < count; e++) 
    { 
        ck = production[e][0]; 
        point2 = 0; 
        xxx = 0; 
           
        for(kay = 0; kay <= ptr; kay++) 
            if(ck == donee[kay]) //check if follow set for ck already calc. 
                xxx = 1; 
                  
        if (xxx == 1) 
            continue; 
        land += 1; 
       
        follow(ck); //function call for follow set calc.
        ptr += 1; 
        donee[ptr] = ck;// Adding ck to the calculated list 
        printf(" Follow(%c) = { ", ck); 
        calc_follow[point1][point2++] = ck; 
          
        // Printing the Follow Sets of the grammar 
        for(i = 0 + km; i < m; i++) { 
            int lk = 0, chk = 0; 
            for(lk = 0; lk < point2; lk++)  
            { 
                if (f[i] == calc_follow[point1][lk]) 
                { 
                    chk = 1; 
                    break; 
                } 
            } 
            if(chk == 0) 
            { 
                printf("%c, ", f[i]); 
                calc_follow[point1][point2++] = f[i]; 
            } 
        } 
        printf(" }\n\n"); 
        km = m; 
        point1++;  
    } 
    
printf("********Parse Table for Grammar:\n");
Parse_tab();

} 

//function def.
void follow(char c) 
{ 
    int i, j; 
      
    // Add "$" to the follow set of the start symbol 
    if(production[0][0] == c) { 
        f[m++] = '$'; 
    } 
    for(i = 0; i < 10; i++) 
    { 
        for(j = 2;j < 10; j++) 
        { 
            if(production[i][j] == c) 
            { 
                if(production[i][j+1] != '\0') 
                { 
                    //Calc the first of the next Non-Terminal in the production 
                    followfirst(production[i][j+1], i, (j+2)); 
                } 
                  
                if(production[i][j+1]=='\0' && c!=production[i][0]) 
                { 
                    // Calculate the follow in the L.H.S. of the production 
                    follow(production[i][0]); 
                } 
            }  
        } 
    } 
} 
  
void first_set(char c, int q1, int q2) 
{ 
    int j; 
      
      
    //when we  encounter a Terminal i.e. small letters. 
    if((islower(c))) { 
        first[n++] = c;
    } 
    for(j = 0; j < count; j++) 
    { 
        if(production[j][0] == c) 
        { 
            if(production[j][2] == '#') // # represents epsilon. 
            { 
                if(production[q1][q2] == '\0') 
                    first[n++] = '#'; 
                else if(production[q1][q2] != '\0' 
                          && (q1 != 0 || q2 != 0)) 
                { 
                  //Recursion for First of new Non-Terminal we encounter after epsilon 
                    first_set(production[q1][q2], q1, (q2+1)); 
                } 
                else
                    first[n++] = '#'; 
            } 
            else if(islower(production[j][2])) 
            { 
                first[n++] = production[j][2]; 
		Table[0][x++]=production[j][2];
            } 
            else 
            { 
                // Recursion to calculate First of new non terminal.
                first_set(production[j][2], j, 3); 
            } 
        } 
    }  
} 
  
void followfirst(char c, int c1, int c2) 
{ 
    int k; 
      
   
    //when we encounter  a Terminal. 
    if((islower(c))) 
        f[m++] = c; 
    else
    { 
        int i = 0, j = 1; 
        for(i = 0; i < count; i++) 
        { 
            if(calc_first[i][0] == c) 
                break; 
        } 
          
        //Including the First set of Non-Terminal in the Follow of original. 
        
        while(calc_first[i][j] != '!') 
        { 
            if(calc_first[i][j] != '#')  
            { 
                f[m++] = calc_first[i][j]; 
            } 
            else
            { 
                if(production[c1][c2] == '\0') 
                { 
                    // Case where we reach the end of production.
                    follow(production[c1][0]); 
                } 
                else
                { 
                    // Recursion to the next symbol if epsilon encountered.
                    followfirst(production[c1][c2], c1, c2+1); 
                } 
            } 
            j++; 
        } 
    } 
}



