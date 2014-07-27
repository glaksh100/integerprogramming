{\rtf1\ansi\ansicpg1252\cocoartf1265\cocoasubrtf210
{\fonttbl\f0\fnil\fcharset0 Menlo-Regular;}
{\colortbl;\red255\green255\blue255;\red0\green116\blue0;\red100\green56\blue32;\red196\green26\blue22;
\red170\green13\blue145;\red92\green38\blue153;\red28\green0\blue207;\red63\green110\blue116;\red46\green13\blue110;
\red14\green14\blue255;\red38\green71\blue75;}
\margl1440\margr1440\vieww10800\viewh8400\viewkind0
\deftab529
\pard\tx529\pardeftab529\pardirnatural

\f0\fs22 \cf2 \CocoaLigature0 // IE511: Integer Programming\cf0 \
\cf2 // A Sudoku Solver in C++ written by Prof. R.S. Sreenivas\cf0 \
\cf2 //\cf0 \
\cf2 // There is an ILP formulation for any 9 x 9 Sudoku Puzzle\cf0 \
\cf2 // See the handout for the formulation -- there are 729 variables\cf0 \
\cf2 // with a whole lot of constraints that is driven by the input\cf0 \
\cf2 // (which is the incomplete board-layout).  You can write this\cf0 \
\cf2 // (moderate-size) ILP automatically in C++, which is then solved\cf0 \
\cf2 // using the API for Lpsolve.\cf0 \
\
\cf3 #include \cf4 <iostream>\cf3 \
#include \cf4 <iomanip>\cf3 \
#include \cf4 <cmath>\cf3 \
#include \cf4 <fstream>\cf3 \
#include \cf4 <cstdlib>\cf3 \
\cf0 \
\cf3 #include \cf4 "/Users/lrao/Documents/UIUC_stuff/UIUC_Acads/IE_511/lp_solve_5.5/lp_lib.h"\cf3 \
\cf0 \
\cf5 using\cf0  \cf5 namespace\cf0  \cf6 std\cf0 ;\
\
\cf2 // Global variables for the problem 9*9*9 = 729\cf0 \
\cf2 // See my handout for further explanations\cf0 \
\cf6 lprec\cf0  *lp;\
\cf5 double\cf0  solution[\cf7 729\cf0 ];\
\
\cf2 // This sets the generic ILP for the Sudoku Puzzle\cf0 \
\cf2 // It does not use any of the pre-determined board-positions,\cf0 \
\cf2 // that part is done after the input file is read.\cf0 \
\cf5 void\cf0  set_sudoku_ilp()\
\{\
	\cf2 // setting the problem up: 9*9*9 = 729 variables\cf0 \
	\cf8 lp\cf0  = \cf9 make_lp\cf0 (\cf7 0\cf0 ,\cf7 729\cf0 );\
	\
	\cf2 // This keeps the message reporting of lp_solve to a minimum\cf0 \
	\cf9 set_verbose\cf0 (\cf8 lp\cf0 , \cf7 3\cf0 );\
	\
	\{\
		\cf5 for\cf0  (\cf5 int\cf0  i = \cf7 1\cf0 ; i <= \cf7 9\cf0 ; i++)\
		\{\
			\cf5 for\cf0  (\cf5 int\cf0  j = \cf7 1\cf0 ; j <= \cf7 9\cf0 ; j++)\
			\{\
				\cf2 // constraint that says each (i,j) entry in the 9x9 table\cf0 \
				\cf2 // should have one number in it\cf0 \
				\cf2 // creating a row with 1's at the right spot (the first\cf0 \
				\cf2 // entry has to be a zero; this is idiosynchratic of lpsolve)\cf0 \
				\
				\cf5 double\cf0  row[\cf7 730\cf0 ];\
				\cf5 for\cf0  (\cf5 int\cf0  k = \cf7 0\cf0 ; k < \cf7 730\cf0 ; k++)\
					row[k] = \cf7 0\cf0 ;\
                \
				\
				\cf5 for\cf0  (\cf5 int\cf0  k = \cf7 1\cf0 ; k <= \cf7 9\cf0 ; k++)\
                    \
					row[(\cf7 81\cf0 *(i-\cf7 1\cf0 )) + (\cf7 9\cf0 *(j-\cf7 1\cf0 )) + k] = \cf7 1\cf0 ;\
				\
				\cf2 // adding the constraint\cf0 \
				\cf9 add_constraint\cf0 (\cf8 lp\cf0 , row, \cf3 EQ\cf0 , \cf7 1\cf0 );\
			\}\
		\}\
	\}\
	\
	\{\
		\cf2 // Using the above code as a guide, put the appropriate lines that\cf0 \
		\cf2 // articulate the constraint that says each number must appear once\cf0 \
		\cf2 // in each row in the 9x9 table; create a bunch of rows with 1's at\cf0 \
		\cf2 // the right spot (the first entry has to be a zero; this is\cf0 \
		\cf2 // idiosynchratic of lpsolve)\cf0 \
		\
		\cf5 for\cf0  (\cf5 int\cf0  i = \cf7 1\cf0 ; i <= \cf7 9\cf0 ; i++)\
		\{\
			\cf5 for\cf0  (\cf5 int\cf0  j = \cf7 1\cf0 ; j <= \cf7 9\cf0 ; j++)\
			\{\
                \
				\cf5 double\cf0  row[\cf7 730\cf0 ];\
				\cf5 for\cf0  (\cf5 int\cf0  k = \cf7 0\cf0 ; k < \cf7 730\cf0 ; k++)\
					row[k] = \cf7 0\cf0 ;\
				\
				\cf5 for\cf0  (\cf5 int\cf0  k = \cf7 1\cf0 ; k <= \cf7 9\cf0 ; k++)\
					row[(\cf7 9\cf0 *(k-\cf7 1\cf0 )) + j +\cf7 81\cf0 *(i-\cf7 1\cf0 )] = \cf7 1\cf0 ;\
                \cf9 add_constraint\cf0 (\cf8 lp\cf0 , row, \cf3 EQ\cf0 , \cf7 1\cf0 );\
            \}\
        \}\
	\}\
	\
	\{\
		\cf2 // Using the above code as a guide, put the appropriate lines that\cf0 \
		\cf2 // articulate the constraint that says each number must appear once\cf0 \
		\cf2 // in each column in the 9x9 table; create a bunch of rows with 1's at\cf0 \
		\cf2 // the right spot (the first entry has to be a zero; this is\cf0 \
		\cf2 // idiosynchratic of lpsolve)\cf0 \
        \
		\cf5 for\cf0  (\cf5 int\cf0  i = \cf7 1\cf0 ; i <= \cf7 9\cf0 ; i++)\
		\{\
			\cf5 for\cf0  (\cf5 int\cf0  j = \cf7 1\cf0 ; j <= \cf7 9\cf0 ; j++)\
			\{\
                \
				\cf5 double\cf0  row[\cf7 730\cf0 ];\
				\cf5 for\cf0  (\cf5 int\cf0  k = \cf7 0\cf0 ; k < \cf7 730\cf0 ; k++)\
					row[k] = \cf7 0\cf0 ;\
				\
				\cf5 for\cf0  (\cf5 int\cf0  k = \cf7 1\cf0 ; k <= \cf7 9\cf0 ; k++)\
					row[(\cf7 81\cf0 *(k-\cf7 1\cf0 )) + j +\cf7 9\cf0 *(i-\cf7 1\cf0 )] = \cf7 1\cf0 ;\
                \cf9 add_constraint\cf0 (\cf8 lp\cf0 , row, \cf3 EQ\cf0 , \cf7 1\cf0 );\
            \}\
        \}\
        \
	\}\
	\
	\cf2 // making sure each number occurs once within each block\cf0 \
	\cf2 // Block 1\cf0 \
	\{\
		\
        \
        \
        \cf5 for\cf0  (\cf5 int\cf0  k = \cf7 1\cf0 ; k <= \cf7 9\cf0 ; k++)\
		\{\
			 \cf5 double\cf0  row[\cf7 730\cf0 ];\
             \cf5 for\cf0  (\cf5 int\cf0   t= \cf7 0\cf0 ; t < \cf7 730\cf0 ; t++)\
                row[t] = \cf7 0\cf0 ;\
            \cf2 // Using the above code as a guide, put the appropriate lines that\cf0 \
			\cf2 // articulate theconstraint that says each number must appear once\cf0 \
			\cf2 // in each 3 x 3 block; create a bunch of rows with 1's at the right\cf0 \
			\cf2 // spot (the first entry has to be a zero; this is idiosynchratic of\cf0 \
			\cf2 // lpsolve)\cf0 \
            \cf5 for\cf0  (\cf5 int\cf0  i=\cf7 1\cf0 ;i<=\cf7 3\cf0 ;i++)\
            \{\
               \
                \cf5 for\cf0 (\cf5 int\cf0  j=\cf7 1\cf0 ; j<=\cf7 3\cf0 ;j++)\
                    row[k+\cf7 81\cf0 *(i-\cf7 1\cf0 )+\cf7 9\cf0 *(j-\cf7 1\cf0 )]=\cf7 1\cf0 ;\
                \
            \}\
            \cf9 add_constraint\cf0 (\cf8 lp\cf0 , row, \cf3 EQ\cf0 , \cf7 1\cf0 );\
		\}\
	\}\
	\
	\cf2 // Block 2\cf0 \
	\{\
		\cf5 for\cf0  (\cf5 int\cf0  k = \cf7 1\cf0 ; k <= \cf7 9\cf0 ; k++)\
		\{\
            \cf5 double\cf0  row[\cf7 730\cf0 ];\
            \cf5 for\cf0  (\cf5 int\cf0  t = \cf7 0\cf0 ; t < \cf7 730\cf0 ; t++)\
                row[t] = \cf7 0\cf0 ;\
			\cf2 // Using the above code as a guide, put the appropriate lines that\cf0 \
			\cf2 // articulate theconstraint that says each number must appear once\cf0 \
			\cf2 // in each 3 x 3 block; create a bunch of rows with 1's at the right\cf0 \
			\cf2 // spot (the first entry has to be a zero; this is idiosynchratic of\cf0 \
			\cf2 // lpsolve)\cf0 \
            \cf5 for\cf0  (\cf5 int\cf0  i=\cf7 4\cf0 ;i<=\cf7 6\cf0 ;i++)\
            \{\
               \
                \cf5 for\cf0 (\cf5 int\cf0  j=\cf7 1\cf0 ; j<=\cf7 3\cf0 ;j++)\
                    row[k+\cf7 81\cf0 *(i-\cf7 1\cf0 )+\cf7 9\cf0 *(j-\cf7 1\cf0 )]=\cf7 1\cf0 ;\
               \
            \}\
             \cf9 add_constraint\cf0 (\cf8 lp\cf0 , row, \cf3 EQ\cf0 , \cf7 1\cf0 );\
            \
		\}\
	\}\
	\
	\cf2 // Block 3\cf0 \
	\{\
		\cf5 for\cf0  (\cf5 int\cf0  k = \cf7 1\cf0 ; k <= \cf7 9\cf0 ; k++)\
            \
		\{\
            \cf5 double\cf0  row[\cf7 730\cf0 ];\
            \cf5 for\cf0  (\cf5 int\cf0  t = \cf7 0\cf0 ; t < \cf7 730\cf0 ; t++)\
                row[t] = \cf7 0\cf0 ;\
			\cf2 // Using the above code as a guide, put the appropriate lines that\cf0 \
			\cf2 // articulate theconstraint that says each number must appear once\cf0 \
			\cf2 // in each 3 x 3 block; create a bunch of rows with 1's at the right\cf0 \
			\cf2 // spot (the first entry has to be a zero; this is idiosynchratic of\cf0 \
			\cf2 // lpsolve)\cf0 \
            \cf5 for\cf0  (\cf5 int\cf0  i=\cf7 7\cf0 ;i<=\cf7 9\cf0 ;i++)\
            \{\
               \
                \cf5 for\cf0 (\cf5 int\cf0  j=\cf7 1\cf0 ; j<=\cf7 3\cf0 ;j++)\
                    row[k+\cf7 81\cf0 *(i-\cf7 1\cf0 )+\cf7 9\cf0 *(j-\cf7 1\cf0 )]=\cf7 1\cf0 ;\
\
            \}\
            \
        \cf9 add_constraint\cf0 (\cf8 lp\cf0 , row, \cf3 EQ\cf0 , \cf7 1\cf0 );\
		\}\
	\}\
	\
	\cf2 // Block 4\cf0 \
	\{\
		\cf5 for\cf0  (\cf5 int\cf0  k = \cf7 1\cf0 ; k <= \cf7 9\cf0 ; k++)\
		\{\
			\cf5 double\cf0  row[\cf7 730\cf0 ];\
            \cf5 for\cf0  (\cf5 int\cf0  t = \cf7 0\cf0 ; t < \cf7 730\cf0 ; t++)\
                row[t] = \cf7 0\cf0 ;\
            \cf2 // Using the above code as a guide, put the appropriate lines that\cf0 \
			\cf2 // articulate theconstraint that says each number must appear once\cf0 \
			\cf2 // in each 3 x 3 block; create a bunch of rows with 1's at the right\cf0 \
			\cf2 // spot (the first entry has to be a zero; this is idiosynchratic of\cf0 \
			\cf2 // lpsolve)\cf0 \
            \cf5 for\cf0  (\cf5 int\cf0  i=\cf7 1\cf0 ;i<=\cf7 3\cf0 ;i++)\
            \{\
                \
                \cf5 for\cf0 (\cf5 int\cf0  j=\cf7 4\cf0 ; j<=\cf7 6\cf0 ;j++)\
                    row[k+\cf7 81\cf0 *(i-\cf7 1\cf0 )+\cf7 9\cf0 *(j-\cf7 1\cf0 )]=\cf7 1\cf0 ;\
                \
            \}\
            \cf9 add_constraint\cf0 (\cf8 lp\cf0 , row, \cf3 EQ\cf0 , \cf7 1\cf0 );\
		\}\
	\}\
	\
	\cf2 // Block 5\cf0 \
	\{\
		\cf5 for\cf0  (\cf5 int\cf0  k = \cf7 1\cf0 ; k <= \cf7 9\cf0 ; k++)\
		\{\
            \cf5 double\cf0  row[\cf7 730\cf0 ];\
            \cf5 for\cf0  (\cf5 int\cf0  t = \cf7 0\cf0 ; t < \cf7 730\cf0 ; t++)\
                row[t] = \cf7 0\cf0 ;\
			\cf2 // Using the above code as a guide, put the appropriate lines that\cf0 \
			\cf2 // articulate theconstraint that says each number must appear once\cf0 \
			\cf2 // in each 3 x 3 block; create a bunch of rows with 1's at the right\cf0 \
			\cf2 // spot (the first entry has to be a zero; this is idiosynchratic of\cf0 \
			\cf2 // lpsolve)\cf0 \
            \cf5 for\cf0  (\cf5 int\cf0  i=\cf7 4\cf0 ;i<=\cf7 6\cf0 ;i++)\
            \{\
                \
                \cf5 for\cf0 (\cf5 int\cf0  j=\cf7 4\cf0 ; j<=\cf7 6\cf0 ;j++)\
                    row[k+\cf7 81\cf0 *(i-\cf7 1\cf0 )+\cf7 9\cf0 *(j-\cf7 1\cf0 )]=\cf7 1\cf0 ;\
                \
            \}\
            \cf9 add_constraint\cf0 (\cf8 lp\cf0 , row, \cf3 EQ\cf0 , \cf7 1\cf0 );\
		\}\
	\}\
	\
	\cf2 // Block 6\cf0 \
	\{\
		\cf5 for\cf0  (\cf5 int\cf0  k = \cf7 1\cf0 ; k <= \cf7 9\cf0 ; k++)\
		\{\
            \cf5 double\cf0  row[\cf7 730\cf0 ];\
            \cf5 for\cf0  (\cf5 int\cf0  t = \cf7 0\cf0 ; t < \cf7 730\cf0 ; t++)\
                row[t] = \cf7 0\cf0 ;\
			\cf2 // Using the above code as a guide, put the appropriate lines that\cf0 \
			\cf2 // articulate theconstraint that says each number must appear once\cf0 \
			\cf2 // in each 3 x 3 block; create a bunch of rows with 1's at the right\cf0 \
			\cf2 // spot (the first entry has to be a zero; this is idiosynchratic of\cf0 \
			\cf2 // lpsolve)\cf0 \
            \cf5 for\cf0  (\cf5 int\cf0  i=\cf7 7\cf0 ;i<=\cf7 9\cf0 ;i++)\
            \{\
                \
                \cf5 for\cf0 (\cf5 int\cf0  j=\cf7 4\cf0 ; j<=\cf7 6\cf0 ;j++)\
                    row[k+\cf7 81\cf0 *(i-\cf7 1\cf0 )+\cf7 9\cf0 *(j-\cf7 1\cf0 )]=\cf7 1\cf0 ;\
            \}\
            \cf9 add_constraint\cf0 (\cf8 lp\cf0 , row, \cf3 EQ\cf0 , \cf7 1\cf0 );\
\
		\}\
	\}\
	\
	\cf2 // Block 7\cf0 \
	\{\
		\cf5 for\cf0  (\cf5 int\cf0  k = \cf7 1\cf0 ; k <= \cf7 9\cf0 ; k++)\
		\{\
            \cf5 double\cf0  row[\cf7 730\cf0 ];\
            \cf5 for\cf0  (\cf5 int\cf0  t = \cf7 0\cf0 ; t < \cf7 730\cf0 ; t++)\
                row[t] = \cf7 0\cf0 ;\
			\cf2 // Using the above code as a guide, put the appropriate lines that\cf0 \
			\cf2 // articulate theconstraint that says each number must appear once\cf0 \
			\cf2 // in each 3 x 3 block; create a bunch of rows with 1's at the right\cf0 \
			\cf2 // spot (the first entry has to be a zero; this is idiosynchratic of\cf0 \
			\cf2 // lpsolve)\cf0 \
            \cf5 for\cf0  (\cf5 int\cf0  i=\cf7 1\cf0 ;i<=\cf7 3\cf0 ;i++)\
            \{\
               \
                \cf5 for\cf0 (\cf5 int\cf0  j=\cf7 7\cf0 ; j<=\cf7 9\cf0 ;j++)\
                    row[k+\cf7 81\cf0 *(i-\cf7 1\cf0 )+\cf7 9\cf0 *(j-\cf7 1\cf0 )]=\cf7 1\cf0 ;\
                \
            \}\
            \cf9 add_constraint\cf0 (\cf8 lp\cf0 , row, \cf3 EQ\cf0 , \cf7 1\cf0 );\
		\}\
	\}\
	\
	\cf2 // Block 8\cf0 \
	\{\
		\cf5 for\cf0  (\cf5 int\cf0  k = \cf7 1\cf0 ; k <= \cf7 9\cf0 ; k++)\
		\{\
            \cf5 double\cf0  row[\cf7 730\cf0 ];\
            \cf5 for\cf0  (\cf5 int\cf0  t = \cf7 0\cf0 ; t < \cf7 730\cf0 ; t++)\
                row[t] = \cf7 0\cf0 ;\
            \cf2 // Using the above code as a guide, put the appropriate lines that\cf0 \
			\cf2 // articulate theconstraint that says each number must appear once\cf0 \
			\cf2 // in each 3 x 3 block; create a bunch of rows with 1's at the right\cf0 \
			\cf2 // spot (the first entry has to be a zero; this is idiosynchratic of\cf0 \
			\cf2 // lpsolve)\cf0 \
            \cf5 for\cf0  (\cf5 int\cf0  i=\cf7 4\cf0 ;i<=\cf7 6\cf0 ;i++)\
            \{\
               \
                \cf5 for\cf0 (\cf5 int\cf0  j=\cf7 7\cf0 ; j<=\cf7 9\cf0 ;j++)\
                    row[k+\cf7 81\cf0 *(i-\cf7 1\cf0 )+\cf7 9\cf0 *(j-\cf7 1\cf0 )]=\cf7 1\cf0 ;\
                \
            \}\
            \cf9 add_constraint\cf0 (\cf8 lp\cf0 , row, \cf3 EQ\cf0 , \cf7 1\cf0 );\
		\}\
	\}\
	\
	\cf2 // Block 9\cf0 \
	\{\
		\cf5 for\cf0  (\cf5 int\cf0  k = \cf7 1\cf0 ; k <= \cf7 9\cf0 ; k++)\
		\{\
            \cf5 double\cf0  row[\cf7 730\cf0 ];\
            \cf5 for\cf0  (\cf5 int\cf0  t = \cf7 0\cf0 ; t < \cf7 730\cf0 ; t++)\
                row[t] = \cf7 0\cf0 ;\
            \cf2 // Using the above code as a guide, put the appropriate lines that\cf0 \
			\cf2 // articulate theconstraint that says each number must appear once\cf0 \
			\cf2 // in each 3 x 3 block; create a bunch of rows with 1's at the right\cf0 \
			\cf2 // spot (the first entry has to be a zero; this is idiosynchratic of\cf0 \
			\cf2 // lpsolve)\cf0 \
            \cf5 for\cf0  (\cf5 int\cf0  i=\cf7 7\cf0 ;i<=\cf7 9\cf0 ;i++)\
            \{\
               \
                \cf5 for\cf0 (\cf5 int\cf0  j=\cf7 7\cf0 ; j<=\cf7 9\cf0 ;j++)\
                    row[k+\cf7 81\cf0 *(i-\cf7 1\cf0 )+\cf7 9\cf0 *(j-\cf7 1\cf0 )]=\cf7 1\cf0 ;\
               \
            \}\
             \cf9 add_constraint\cf0 (\cf8 lp\cf0 , row, \cf3 EQ\cf0 , \cf7 1\cf0 );\
		\}\
	\}\
	\
	\cf2 // upper-bound each variable by 1\cf0 \
	\cf5 for\cf0  (\cf5 int\cf0  i = \cf7 1\cf0 ; i <= \cf7 729\cf0 ; i++)\
	\{\
		\cf5 double\cf0  row[\cf7 730\cf0 ];\
		\cf5 for\cf0  (\cf5 int\cf0  j = \cf7 0\cf0 ; j < \cf7 730\cf0 ; j++)\
			row[j] = \cf7 0\cf0 ;\
		row[i] = \cf7 1\cf0 ;\
		\cf9 add_constraint\cf0 (\cf8 lp\cf0 , row, \cf3 LE\cf0 , \cf7 1\cf0 );\
	\}\
	\
	\cf2 // it does not matter what the objective function (why?)\cf0 \
	\cf2 // I am minimizing the sum of all variables.\cf0 \
	\{\
		\cf5 double\cf0  row[\cf7 730\cf0 ];\
		\cf5 for\cf0  (\cf5 int\cf0  i = \cf7 1\cf0 ; i < \cf7 730\cf0 ; i++)\
			row[i] = \cf7 1\cf0 ;\
		row[\cf7 0\cf0 ] = \cf7 0\cf0 ;\
		\
		\cf9 set_obj_fn\cf0 (\cf8 lp\cf0 , row);\
	\}\
	\
	\cf2 // set the variables to be integers\cf0 \
	\cf5 for\cf0  (\cf5 int\cf0  i = \cf7 1\cf0 ; i <= \cf7 729\cf0 ; i++)\
		\cf9 set_int\cf0 (\cf8 lp\cf0 , i, \cf5 TRUE\cf0 );\
\}\
\
\cf2 // This subroutine reads the incomplete board-information from the\cf0 \
\cf2 // input file and sets the appropriate constraints before the ILP\cf0 \
\cf2 // is solved.\cf0 \
\cf5 void\cf0  read_input_data(\cf5 char\cf0 * argv[])\
\{\
	\cf2 // reading the input filename from commandline\cf0 \
	\cf6 ifstream\cf0  input_filename(argv[\cf7 1\cf0 ]);\
	\
	\cf5 if\cf0  (input_filename.\cf9 is_open\cf0 ()) \{\
		\
		\cf6 cout\cf0  << \cf4 "Input File Name: "\cf0  << argv[\cf7 1\cf0 ] << \cf9 endl\cf0 ;\
		\cf6 cout\cf0  << \cf9 endl\cf0  << \cf4 "Initial Board Position"\cf0  << \cf9 endl\cf0 ;\
		\cf5 for\cf0  (\cf5 int\cf0  i = \cf7 1\cf0 ; i <= \cf7 9\cf0 ; i++)\
		\{\
			\cf5 for\cf0  (\cf5 int\cf0  j = \cf7 1\cf0 ; j <= \cf7 9\cf0 ; j++)\
			\{\
				\cf5 int\cf0  value_just_read;\
				input_filename >> value_just_read;\
				\
				\cf2 // check if we have a legitimate integer between 1 and 9\cf0 \
				\cf5 if\cf0  ((value_just_read >= \cf7 1\cf0 ) && (value_just_read <= \cf7 9\cf0 ))\
				\{\
					\cf2 // printing initial value of the puzzle with some formatting\cf0 \
					\cf6 cout\cf0  << value_just_read << \cf4 " "\cf0 ;\
					\
					\cf2 // add appropriate constraints that bind the value of the\cf0 \
					\cf2 // appropriate variables based on the incomplete information\cf0 \
					\cf2 // that was read from the input file\cf0 \
                    \cf5 double\cf0  row[\cf7 730\cf0 ];\
                    \cf5 for\cf0  (\cf5 int\cf0  k = \cf7 0\cf0 ; k < \cf7 730\cf0 ; k++)\
                        row[k] = \cf7 0\cf0 ;\
                    \
                   \
                        row[(\cf7 81\cf0 *(i-\cf7 1\cf0 )) + value_just_read +\cf7 9\cf0 *(j-\cf7 1\cf0 )] = \cf7 1\cf0 ;\
                    \cf9 add_constraint\cf0 (\cf8 lp\cf0 , row, \cf3 EQ\cf0 , \cf7 1\cf0 );\
                    \
				\}\
				\cf5 else\cf0  \{\
					\cf2 // printing initial value of the puzzle with some formatting\cf0 \
					\cf6 cout\cf0  << \cf4 "X "\cf0 ;\
				\}\
                \
			\}\
			\cf6 cout\cf0  << \cf9 endl\cf0 ;\
		\}\
	\}\
	\cf5 else\cf0  \{\
		\cf6 cout\cf0  << \cf4 "Input file missing"\cf0  << \cf9 endl\cf0 ;\
		\cf9 exit\cf0 (\cf7 0\cf0 );\
	\}\
\}\
\
\cf2 // The ILP formulation is solved using the API for Lpsolve\cf0 \
\cf2 // Pay attention to how the solution is interpretted...\cf0 \
\cf5 void\cf0  solve_the_puzzle()\
\{\
	\cf5 int\cf0  ret;\
	\cf2 // solve the lp\cf0 \
	ret = \cf9 solve\cf0 (\cf8 lp\cf0 );\
   	\
	\cf2 // Check if you had a solution\cf0 \
	\cf2 // (see online guide for the codes at {\field{\*\fldinst{HYPERLINK "http://lpsolve.sourceforge.net/5.0/"}}{\fldrslt \cf10 http://lpsolve.sourceforge.net/5.0/}} )\cf0 \
	\cf5 if\cf0  (ret == \cf7 0\cf0 )\
	\{\
		\
		\cf2 // get the optimal assignment\cf0 \
		\cf9 get_variables\cf0 (\cf8 lp\cf0 , \cf8 solution\cf0 );\
		\
		\cf2 // print the solution\cf0 \
		\cf6 cout\cf0  << \cf9 endl\cf0  << \cf4 "Final Solution"\cf0  << \cf9 endl\cf0 ;\
		\{\
			\cf5 for\cf0  (\cf5 int\cf0  i = \cf7 1\cf0 ; i <= \cf7 9\cf0 ; i++)\
			\{\
				\cf5 for\cf0  (\cf5 int\cf0  j = \cf7 1\cf0 ; j <= \cf7 9\cf0 ; j++)\
				\{\
					\cf5 for\cf0  (\cf5 int\cf0  k = \cf7 1\cf0 ; k <= \cf7 9\cf0 ; k++)\
					\{\
						\cf5 if\cf0  (\cf8 solution\cf0 [(\cf7 81\cf0 *(i-\cf7 1\cf0 )) + (\cf7 9\cf0 *(j-\cf7 1\cf0 )) + k - \cf7 1\cf0 ] == \cf7 1\cf0 )\
							\cf6 cout\cf0  << k << \cf4 " "\cf0 ;\
					\}\
				\}\
				\cf6 cout\cf0  << \cf9 endl\cf0 ;\
			\}\
		\}\
	\}\
	\cf5 else\cf0  \{\
		\cf6 cout\cf0  << \cf4 "Check the input file... looks like there is no solution"\cf0  << \cf9 endl\cf0 ;\
	\}\
    \
	\
	\cf9 delete_lp\cf0 (\cf8 lp\cf0 );\
\}\
\
\cf5 int\cf0  main (\cf5 int\cf0  argc, \cf5 char\cf0 * argv[])\
\{\
	\cf2 // formulate the non-input related part of the puzzle\cf0 \
	\cf11 set_sudoku_ilp\cf0 ();\
	\
	\cf2 // read the incomplete input information, and set appropriate constraints\cf0 \
	\cf11 read_input_data\cf0 (argv);\
	\
	\cf2 // solve the puzzle and print the solution\cf0 \
	\cf11 solve_the_puzzle\cf0 ();\
	\
	\cf5 return\cf0 (\cf7 0\cf0 );\
\}\
}