// Michelle Ly
// mly8
// pa3

public class List {
	// Node and List Objects ------------------------------------------------------

	private Node front;
	private Node back;
	private Node cursor;
	private int length;
	private int index;
	List(){
		front = new Node(-1);
		back = front;
		front.next = back;
		back.prev = front;
		length = 0;
		index = -1;
	}
	
	public class Node{
		int data;
		Node next;
		Node prev;
		
		Node(int data){
			this.data = data;
			next = null;
			prev = null;
		}
	}
	
	// Access functions -----------------------------------------------------------
	// Returns the number of elements in this List.
	int length(){
		return length;
	}
	// If cursor is defined, returns the index of the cursor element,
	// otherwise returns -1
	int index(){
		if(cursor == null){
			return -1;
		}
		return index;
	}
	// Returns front element. Pre: length()>0
	int front(){
		if (length() <= 0) {
			throw new RuntimeException("Runtime Error! " + "// Method: front() " + "// Reason: length() <= 0");
		}
		return front.data;
	}
	// Returns back element. Pre: length()>0
	int back(){
		if (length() <= 0) {
			throw new RuntimeException("Runtime Error! " + "// Method: back() " + "// Reason: length() <= 0");
		}
		return back.data;
	}
	// Returns cursor element. Pre: length()>0, index()>=0
	int get(){
		if (length() <= 0) {
			throw new RuntimeException("Runtime Error! " + "// Method: get() " + "// Reason: length() <= 0");
		}
		if (index() < 0) {
			throw new RuntimeException("Runtime Error! " + "// Method: get() " + "// Reason: index() < 0");
		}
		return cursor.data;
	}
	// Returns true if this List and L are the same integer
	// sequence. The cursor is ignored in both lists.
	boolean equals(List L){
		boolean eq;
		Node N = null;
		Node M = null;
		eq = (length() == length);
		N = front;
		M = front;
		while (eq && N != null) {
			eq = (N.data == M.data);
			N = N.next;
			M = M.next;
		}
		return eq;
	}
	// Manipulation procedures ----------------------------------------------------
	// Resets this List to its original empty state.
	void clear(){
		front = null;
		back = null;
		cursor = null;
		index = -1;
		length = 0;
	}
	// If List is non-empty, places the cursor under the front element,
	// otherwise does nothing.
	void moveFront(){
		if(length() > 0){
			cursor = front;
			index = 0;
		}
	}
	// If List is non-empty, places the cursor under the back element,
	// otherwise does nothing.
	void moveBack(){
		if(length() > 0){
			cursor = back;
			index = length -1;
		}
	}
	// If cursor is defined and not at front, moves cursor one step toward
	// front of this List, if cursor is defined and at front, cursor becomes
	// undefined, if cursor is undefined does nothing.
	void movePrev(){
		if (index != -1 && cursor == front) {
			index = -1;
			cursor = null;
		}
		if (index != -1 && cursor != front) {
			cursor = cursor.prev;
			index--;
		}       
	}
	// If cursor is defined and not at back, moves cursor one step toward
	// back of this List, if cursor is defined and at back, cursor becomes
	// undefined, if cursor is undefined does nothing.
	void moveNext(){
		if (index != -1 && cursor == back) {
			index = -1;
			cursor = null;
		}
		if (index != -1 && cursor != back) {
			cursor = cursor.next;
			index++;
		}
	}
	// Insert new element into this List. If List is non-empty,
	// insertion takes place before front element.
	void prepend(int data){
		Node N = new Node(data);
		if(length() == 0) { 
			front = back = N;
			front.prev = null;
			back.next = null;
		}else{ 
			front.prev = N; 
			N.next = front;
			front = N; 
		}
		length++;
	}
	// Insert new element into this List. If List is non-empty,
	// insertion takes place after back element.
	void append(int data){
		Node N = new Node(data);
		if(length() == 0) { 
			front = back = N; 
			front.prev = null;
			back.next = null;
		}else{ 
			back.next = N; 
			N.prev = back;
			back = N; 
		}
		length++;
	}
	// Insert new element before cursor.
	// Pre: length()>0, index()>=0
	void insertBefore(int data){
		Node N = new Node(data);
		if(length() == 0){
			throw new RuntimeException("Runtime Error! " + "// Method: insertBefore() " + "// Reason: length() <= 0");
		}
		if(index() < 0){
			throw new RuntimeException("Runtime Error! " + "// Method: insertBefore() " + "// Reason: index() < 0");
		}
		if(index() == 0){
			prepend(data);
		}
		else{
			N.next = cursor;
			N.prev = cursor.prev;
			cursor.prev.next = N;
			cursor.prev = N;
			length++;
		}
	}
	// Inserts new element after cursor.
	// Pre: length()>0, index()>=0
	void insertAfter(int data){
		Node N = new Node(data);
		if(length() == 0){
			throw new RuntimeException("Runtime Error! " + "// Method: insertAfter() " + "// Reason: length() <= 0");
		}
		if(index() < 0){
			throw new RuntimeException("Runtime Error! " + "// Method: insertAfter() " + "// Reason: index() < 0");
		}
		if(index() == length()-1){
			append(data);
		}
		else{
			N.prev = cursor;
			N.next = cursor.next;
			cursor.next.prev = N;
			cursor.next = N;
			length++;
		}
	}
	// Deletes the front element. Pre: length()>0
	void deleteFront(){
		Node N = null;
		if(length() == 0){
			throw new RuntimeException("Runtime Error! " + "// Method: deleteFront() " + "// Reason: length() <= 0");
		}
		if(cursor == front){
			cursor = null;
		}
		N = front;
		if(length() > 1) { 
			front = front.next; 
			front.prev = null;
		}else{ 
			front = back = null; 
		}
		length--;
	}
	// Deletes the back element. Pre: length()>0
	void deleteBack(){
		Node N = null;
		if(length() == 0){
			throw new RuntimeException("Runtime Error! " + "// Method: deleteBack() " + "// Reason: length() <= 0");
		}
		if(cursor == back){
			cursor = null;
		}
		N = back;
		if(length() > 1) { 
			back = back.prev;
			back.next = null;
		}else{ 
			back = front = null; 
		}
		length--;
	}
	// Deletes cursor element, making cursor undefined.
	// Pre: length()>0, index()>=0
	void delete(){
		Node N = null;
		if(length() == 0){
			throw new RuntimeException("Runtime Error! " + "// Method: delete() " + "// Reason: length() <= 0");
		}
		if (index() < 0) {
			throw new RuntimeException("Runtime Error! " + "// Method: delete() " + "// Reason: index() < 0");
		}
		N = cursor;
		if(cursor == front){
			deleteFront();
			length--;
		}
		if(cursor == back){
			deleteBack();
			length--;
		}
		cursor.next.prev = cursor.prev;
		cursor.prev.next = cursor.next;
		length--;
	}
	// Other methods
	// Overrides Object's toString method. Returns a String
	// representation of this List consisting of a space
	// separated sequence of integers, with front on left.
	public String toString() {
		StringBuffer sb = new StringBuffer();
		Node N = front;
		
		while (N != null) {
			sb.append(N.toString());
			sb.append(" ");
			N = N.next;
		}
		return new String(sb);
	}

	// Returns a new List representing the same integer sequence as this
	// List. The cursor in the new list is undefined, regardless of the
	// state of the cursor in this List. This List is unchanged.
	List copy() {
		List Li = new List();
		Node N = this.front;

		while (N != null) {
			Li.append(N.data);
			N = N.next;
		}
		return Li;
	}
}
