#include "my_malloc.h"

static char memblock[memSize];
static const int numEntries = memSize/sizeof(Node)+1;
static void *requestedNode[memSize/sizeof(Node)+1] = {0};
static int numIndex()
{
        int i;
        for (i = 0; i < numEntries; i++)
        {
                if (requestedNode[i] == 0)
		{
                        return i;
                }
        }
}

void *mymalloc(unsigned short size, char *file, int line)
{
	static int firstRun = 0;
	Node *p;
	Node *next;
	static Node *head;
	
	if (size == 0) 
	{
		fprintf(stderr, "Error: unable to allocate 0 bytes.\nError found on LINE: '%d' in FILE: '%s'\n\n", line, file);
		return 0;
	}

	if(!firstRun)	// 1st time called
	{
		head = (Node*) memblock;
		head->prev = head->next = 0;
		head->size = memSize - sizeof(Node);
		head->isFree = 1;
		firstRun = 1;
		requestedNode[numIndex()] = memblock;
	}

		p = head;
	do
	{
		if(p->size < size || !p->isFree) 
		{
			p = p->next;
		}
		else if(p->size < (size + sizeof(Node))) 
		{
			p->isFree = 0;
			return (char*)p + sizeof(Node);
		}
		else 
		{
			next = (Node*)((char*)p + sizeof(Node) + size);
			next->prev = p;
			next->next = p->next;
			next->size = p->size - sizeof(Node) - size;
			next->isFree = 1;
			requestedNode[numIndex()] = next;
			p->size = size;
			p->isFree = 0;
			p->next = next;
			return (char*)p + sizeof(Node);
		}
	} 
	while(p != 0);

	fprintf(stderr, "Error: Insufficient memory space requested (%d bytes).\nError fount on LINE: '%d' in FILE: '%s' \n\n", size, line, file);
	return 0;
}
void myfree(void *p, char *file, int line)
{
	Node *ptr;
	Node *prev;
	Node *next;

	if (p == NULL) 
	{
		fprintf(stderr, "Error: Pointer is NULL, free failed\n Error on LINE: '%d' in FILE: '%s' \n\n", line, file);
		return;
	}
	ptr = (Node*)((char*)p - sizeof(Node));
	
	int i;
	int valid = 0;
	for (i = 0; i < numEntries; i++) 
	{
		if (ptr == requestedNode[i] && !ptr->isFree) 
		{
			valid = 1;
			break;
		}
	}
	if (!valid) 
	{
		fprintf(stderr, "Error: trying to free something that was not malloced.\n Error on LINE: '%d' in FILE: '%s'\n\n", line, file);
		return;
	}
	if((prev = ptr->prev) != 0 && prev->isFree)
	{
		// the previous chunk is free, so
		// merge this chunk with the previous chunk
		prev->size += sizeof(Node) + ptr->size;
		requestedNode[i] = 0;
	}
	else
	{
		ptr->isFree = 1;
		prev = ptr;
	}
	if((next = ptr->next) != 0 && next->isFree)
	{
		prev->size += sizeof(Node) + next->size;
		prev->next = next->next;
		for (i = 0; i < numEntries; i++) 
		{
			if (next == requestedNode[i]) 	
			{
				requestedNode[i] = 0;
				break;
			}
		}
	}
}
