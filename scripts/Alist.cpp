template<typename E>
class Alist{
private:
	int max_size;
	int size;
	E* array;
public:
	Alist(int size){
		this.max_size=size;
		this.array=new E[size];
	}
}