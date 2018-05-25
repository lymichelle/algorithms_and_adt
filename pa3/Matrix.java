// Michelle Ly
// mly8
// pa3

// This Matrix ADT has a private inner class, Entry, to store in values. Its purpose is to
// perform matrix operations on a matrix.
public class Matrix {
        private List[] row;
        private int size;
        private int nnz;
        
        // Inner class Entry
        private class Entry {
                int col;
                double val;
                Entry(int column, double value){
                        col = column;
                        val = value;
                }
                public boolean equals(Object x){
                        boolean eq = false;
                        Entry E;
                        if(x instanceof Entry){
                                E = (Entry)x;
                                if(this.col == E.col){
                                        eq = true;
                                }
                        }
                        return eq;
                }
                public String toString() {
                        return "(" + col + ", " + val + ")";
                }
        }
        
        // Constructor
        // Makes a new n x n zero Matrix. pre: n>=1
        Matrix(int n) {
                if(n < 1){
                        throw new RuntimeException("Runtime Error! " + "// Method: Matrix() " + "// Reason: n < 1");
                }
                row = new List[n+1];
                for(int i = 1; i <= n; i++){
                        row[i] = new List();
                }
                size = n;
                nnz = 0;
        }
        // Access functions
        // Returns n, the number of rows and columns of this Matrix
        int getSize() {
                return size;
        }
        // Returns the number of non-zero entries in this Matrix
        int getNNZ() {
                return nnz;
        }
        // overrides Object's equals() method
        public boolean equals(Object x) {
                Matrix M;
                boolean eq = false;
                if(x instanceof Matrix){
                        M = (Matrix)x;
                        if(getSize() == M.getSize() && getNNZ() == M.getNNZ()){
                                for(int i = 1; i <= getSize(); i++){
                                        if(row[i].equals(M.row[i])){
                                                eq = false;
                                        }
                                }
                                eq = true;
                        }       
                }
                return eq;
        }
        // Manipulation procedures
        // sets this Matrix to the zero state
        void makeZero() {
                row = new List[size+1];
                nnz = 0;
        }
        // returns a new Matrix having the same entries as this Matrix
        Matrix copy() {
                Matrix M = new Matrix(getSize());
                Entry E;
                for(int i = 1; i <= getSize(); ++i) {
                        row[i].moveFront();
                        while(row[i].index() >= 0) {
                                E = (Entry)row[i].get();
                                M.changeEntry(i, E.col, E.val);
                                row[i].moveNext();
                        }
                }
                return M;
        }
        // changes ith row, jth column of this Matrix to x
        // pre: 1<=i<=getSize(), 1<=j<=getSize()
        void changeEntry(int i, int j, double x) {
                if(i < 1 || i > getSize() || j < 1 || j > getSize()){
                        throw new RuntimeException("Runtime Error! " + "// Method: ChangeEntry() " + "// Reason: i or j not between 0 and size + 1");
                }
                Entry E;
                row[i].moveFront();
                if(x != 0 && row[i].length() == 0){
                        row[i].append(new Entry(j, x));
                        nnz++;
                        return;
                }
                for(int k = 1; k <= getSize(); k++){
                        if(row[i].index() >= 0){
                                E = (Entry)row[i].get();
                                if(E.col >= j){
                                        if(x == 0 && E.col > j){
                                                return;
                                        }
                                        if(x == 0 && E.col == j){
                                                row[i].delete();
                                                nnz--;
                                                return;
                                        }
                                        if(x != 0 && E.col > j){
                                                row[i].insertBefore(new Entry(j, x));
                                                nnz++;
                                                return;
                                        }
                                        if(x != 0 && E.col == j){
                                                E.val = x;
                                                return;
                                        }
                                }
                                row[i].moveNext();
                        }
                }
                if(x == 0){
                        return;
                }
                row[i].append(new Entry(j, x));
                nnz++;
        }
        // returns a new Matrix that is the scalar product of this Matrix with x
        Matrix scalarMult(double x) {
                Matrix M = new Matrix(size);
                Entry E;
                if(x == 0 || nnz == 0){
                        return M;
                }
                for(int i = 1; i <= getSize(); i++){
                        if(row[i].length() != 0){
                                row[i].moveFront();
                                for(int j = 1; j <= row[i].length(); j++){
                                        E = (Entry)row[i].get();
                                        M.changeEntry(i,j,x * E.val);
                                        row[i].moveNext();
                                }
                        }
                }
                return M;
        }
        // returns a new Matrix that is the sum of this Matrix with M
        // pre: getSize()==M.getSize()
        Matrix add(Matrix M) {
                if(getSize() != M.getSize()){
                        throw new RuntimeException("Runtime Error! " + "// Method: add() " + "// Reason: Size mismatch");
                }
                Matrix sum = new Matrix(size);
                List[] mRow = M.row;
                Entry E;
                Entry R;
                if(this == M){
                        return this.scalarMult(2);
                }
                for(int i = 1; i <= getSize(); i++){
                        row[i].moveFront();
                        mRow[i].moveFront();
                        while(row[i].index() >= 0 || mRow[i].index() >= 0){
                                if(row[i].index() >= 0 && mRow[i].index() >= 0){
                                        E = (Entry)row[i].get();
                                        R = (Entry)mRow[i].get();
                                        if(E.col < R.col){
                                                sum.row[i].append(new Entry(E.col, E.val));
                                                row[i].moveNext();
                                                sum.nnz++;
                                        }
                                        if(E.col > R.col){
        
                                                sum.row[i].append(new Entry(R.col, R.val));
                                                mRow[i].moveNext();
                                                sum.nnz++;
                                        }
                                        if(E.col == R.col){
                                                if(E.val + R.val != 0){
                                                        sum.row[i].append(new Entry(E.col, E.val + R.val)); 
                                                        sum.nnz++;
                                                }
                                                row[i].moveNext();
                                                mRow[i].moveNext();
                                        }
                                }
                                else if(row[i].index() >= 0){
                                        E = (Entry)row[i].get();
                                        sum.row[i].append(new Entry(E.col, E.val));
                                        row[i].moveNext();
                                        sum.nnz++;
                                }
                                else if(mRow[i].index() >= 0){
                                        R = (Entry)mRow[i].get();
                                        sum.row[i].append(new Entry(R.col, R.val));
                                        mRow[i].moveNext();
                                }
                        }
                }
                return sum;
        }
        // returns a new Matrix that is the difference of this Matrix with M
        // pre: getSize()==M.getSize()
        Matrix sub(Matrix M) {
                if(getSize() != M.getSize()){
                        throw new RuntimeException("Runtime Error! " + "// Method: sub() " + "// Reason: Size mismatch");
                }
                Matrix diff = new Matrix(size);
                diff = add(M.scalarMult(-1));
                return diff;
                
        }
        // returns a new Matrix that is the transpose of this Matrix
        Matrix transpose() {
                Matrix M = new Matrix(size);
                Entry E;
                for(int i = 1; i <= getSize(); i++){
                        row[i].moveFront();
                        while(row[i].index() >= 0){
                                E = (Entry)row[i].get();
                                M.changeEntry(E.col, i, E.val);
                                row[i].moveNext();
                        }
                }
                return M;
        }
        // returns a new Matrix that is the product of this Matrix with M
        // pre: getSize()==M.getSize()
        Matrix mult(Matrix M) {
                if(getSize() != M.getSize()){
                        throw new RuntimeException("Runtime Error! " + "// Method: mult() " + "// Reason: Size mismatch");
                }
                Matrix prod = new Matrix(size);
                Matrix mat = M.transpose();
                List[] mRow = mat.row;
                for(int i = 1; i <= getSize(); i++){
                        //row[i].moveFront();
                        if(row[i].length() != 0){
                                for(int j = 1; j <= getSize(); j++){
                                        if(mRow[j].length() != 0){
                                                //mRow[j].moveFront();
                                                prod.changeEntry(i, j, dot(row[i], mRow[j]));
                                                //prod.nnz++;
                                        }
                                }
                        }       
                }
                return prod;
        }
        // Other functions
        // computes the vector dot product of two matrix rows represented by Lists P and Q
        private static double dot(List P, List Q){
                P.moveFront();
                Q.moveFront();
                double product = 0.0;
                while(P.index() >= 0 && Q.index() >= 0){
                        Entry E = (Entry)P.get();
                        Entry R = (Entry)Q.get();
                        if(E.col < R.col){
                                P.moveNext();
                        }
                        if(E.col > R.col){
                                Q.moveNext();
                        }else{
                        
                                product += (E.val * R.val);
                                P.moveNext();
                                Q.moveNext();   
                        }
                }
                return product;
        }
        
        // overrides Object's toString() method
        public String toString() {
                String read = "";
                for(int i = 1; i < getSize(); i++){
                        if(row[i].length() > 0){
                                read += row[i] + "\n";
                        }
                }
                return read;
        }
}