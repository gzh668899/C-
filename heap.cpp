struct MaxHeap
{
    Section* buffer[MAX_SECTION_CNT];
    int size;
};

MaxHeap maxheap;


void HeapInit(MaxHeap* heap)
{
    heap->size = 0;
}
 
int HeapCmp(Section* s1, Section* s2)
{
    if (s1->size != s2->size)
        return s1->size - s2->size;   // >0,s1优先级高于s2
    return s2->start - s1->start;
}
 
void HeapSwap(MaxHeap* heap, int idx1, int idx2)
{
    Section* temp = heap->buffer[idx1];
    heap->buffer[idx1] = heap->buffer[idx2];
    heap->buffer[idx2] = temp;
    heap->buffer[idx1]->hidx = idx1;
    heap->buffer[idx2]->hidx = idx2;
}
 
void HeapAdjustUpward(MaxHeap* heap, int cidx)
{
    for (int pidx = (cidx - 1) / 2; cidx > 0; pidx = (cidx - 1) / 2)
    {
        if (HeapCmp(heap->buffer[pidx], heap->buffer[cidx]) > 0)
            break;
        HeapSwap(heap, pidx, cidx);
        cidx = pidx;
    }
}
 
void HeapAdjustDownward(MaxHeap* heap, int pidx)
{
    for (int cidx = pidx * 2 + 1; cidx < heap->size; cidx = pidx * 2 + 1)
    {
        if (cidx + 1 < heap->size && HeapCmp(heap->buffer[cidx + 1], heap->buffer[cidx]) > 0)
            cidx++;
        if (HeapCmp(heap->buffer[pidx], heap->buffer[cidx]) > 0)
            break;
        HeapSwap(heap, pidx, cidx);
        pidx = cidx;
    }
}
 
void HeapAdjust(MaxHeap* heap,int idx)
{
    HeapAdjustUpward(heap, idx);
    HeapAdjustDownward(heap, idx);
}
 
void HeapRemove(MaxHeap* heap, Section* node)
{
    if (node->hidx == heap->size - 1)
    {
        heap->size--;
        return;
    }
    int idx = node->hidx;
    HeapSwap(heap, idx, heap->size - 1);
    heap->size--;
    HeapAdjust(heap, idx);
}
 
void HeapPush(MaxHeap* heap, Section* node)
{
    node->hidx = heap->size;
    heap->buffer[heap->size] = node;
    heap->size++;
    if (heap->size > 1)
        HeapAdjustUpward(heap, node->hidx);
}


Cell* HeapPop(MinHeap* heap) {
    if (heap->size == 1) {
        heap->size = 0;
        return heap->buf[0];
    }
    HeapSwap(heap, 0, heap->size - 1);
    heap->size--;
    HeapAdjustDownwards(heap, 0);
    return heap->buf[heap->size];
}
