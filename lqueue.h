    typedef int TElem;

    #ifndef LQUEUE_H_INCLUDED
    #define LQUEUE_H_INCLUDED

    struct Node;
    struct LnkQueue;
    typedef struct Node *PtrToNode;
    typedef struct LnkQueue *PtrToQueue;
    typedef PtrToNode PNode;
    typedef PtrToQueue LQueue;

    int IsEmptyQueue( LQueue Q );
    LQueue CreateQueue( void );
    void RemoveQueue( LQueue *PQ );
    void MakeEmptyQueue( LQueue Q );
    void Enqueue( TElem X, LQueue Q );
    TElem Front( LQueue Q );
    void Dequeue( LQueue Q );
    TElem FrontAndDequeue( LQueue Q );
    void PrintQueue( LQueue Q );

    #endif // LQUEUE_H_INCLUDED
