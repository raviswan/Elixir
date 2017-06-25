#include <stdio.h>
#include <stdlib.h>

void* amalloc(size_t n, size_t alignment){
	size_t offset = alignment -1 +sizeof(void*);
	void*p = malloc(n+offset);
	printf("p=%p, sizeof(void*)=%ld\n",p,sizeof(void*));
	if(p==NULL)
		return NULL;
	void* q = (void*)(((size_t)(p)+offset) & ~(alignment-1));
	printf("q=%p\n",q);
	((void**) q)[-1] = p;
	printf("q[-1]=%p\n",p);
	return q;

}
void afree(void* p){
	void* p1 = ((void**)p)[-1];
	free(p1);
}

	
int main(){
	void* p = amalloc(100,16);
	printf("266&~7=%d\n",266&~7);
	printf("value returned is %p  %p  %p\n",amalloc(100,16),amalloc(100,16),amalloc(100,16));
	return 0;
}
