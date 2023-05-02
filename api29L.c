#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 1024
#define E 50
#define UNDO_SIZE 700000

struct node{
    char * riga;
    int mod;
};

struct history{
    int occ;
    struct node * instance;
    struct history * next;
    struct history * prev;
};


struct istruzioni{
    int i1, i2;
    char m;
};

void append(struct history** head_ref, struct history * last, struct node * inst)
{
    /* 1. allocate node */
    struct history* new_node = calloc(1, sizeof(struct history));

    /* 2. put in the data  */
    new_node->instance = inst;
    /* 3. This new node is going to be the last node, so
          make next of it as NULL*/
    new_node->next = NULL;
    /* 4. If the Linked List is empty, then make the new
          node as head */
    if (*head_ref == NULL) {
        new_node->prev = NULL;
        *head_ref = new_node;
        return;
    }
    /* 6. Change the next of last node */
    last->next = new_node;

    /* 7. Make last node as previous of new node */
    new_node->prev = last;

    return;
}


void main(){
    struct node * root = NULL, * temp=NULL;
    int i=0, n=0, ind1=0, ind2=0, setZero=0, j=0, k=0, maxStack=0, size=0, sp=0, h=0, ind12=0, roll=0, maxIstr=0, oldocc=0, dimStack=0, elements=50, occupate=0, daOccupare=0, nDelete=0, doU=1, shift=0, ciclo=1, flag=0, nIstr=0, ind11=0, ind22=0, nUndo=0, nU=0, nR=0, readfromline=1, t=0;
    char * linea = NULL, line[MAX], mode, * found=NULL, *found1=NULL, *string, *strtmp=NULL, lineBuffer[MAX], throw[MAX];
    struct history * head=NULL, * last=NULL, * new=NULL;
    char  **ptr=NULL, **tmps=NULL, **indexs=NULL, **stack=NULL;
    int * occArr = NULL;
    struct istruzioni * undo=malloc(sizeof(struct istruzioni)*UNDO_SIZE);
    fgets(line, MAX, stdin);//prendo il primo input
    //nIstr++;
    root=(struct node*)malloc(sizeof(struct node));
    append(&head, last, root);
    last=head;
    last->occ=occupate;
    occArr=calloc(elements, sizeof(int));
    //head=root;
    while(line[0]!='q'){//finché non viene immesso q ciclo
        //printf("a. faccio: %s", line);
        string = strdup(line);
        found = strsep(&string, ",");
        ind1 = atoi(found);
        found = strsep(&string, ",");
        for (i = 0; line[i] != '\n'; i++);
        linea=(char*)malloc(sizeof(char)*(i+1));
        strncpy(linea, line, i+1);
        mode = line[i - 1];
        switch (mode) {
            case 'c':
                found1 = strsep(&found, "c");
                break;
            case 'p':
                found1 = strsep(&found, "p");
                break;
            case 'd':
                found1 = strsep(&found, "d");
                break;
            case 'u':
                flag=1;
                break;
            case 'r':
                flag=1;
                break;
        }
        if(flag!=1)
            ind2 = atoi(found1);
        else
            flag=0;
        root=last->instance;

        if(mode=='c') {

            if(nUndo>0 || setZero==1) {
                //dimStack-=nUndo;
                nUndo = 0;

                //stack=realloc(stack, (dimStack)*sizeof(char *));

                dimStack=sp;
                oldocc=sp;
                if(setZero==1)
                    setZero=0;
                //nIstr--;
                //printf("ora sp è %d\n", sp);
            }
            else{
                oldocc=dimStack;
            }

            if(nIstr>=elements){
                elements+=E;
                occArr=realloc(occArr, sizeof(int)*elements);
            }
            undo[nIstr].i1=ind1;
            undo[nIstr].i2=ind2;
            undo[nIstr].m='c';
            *(occArr+nIstr)=occupate;
            if(occupate<ind2){

                //printf("occupate=%d\n", occupate);
                if(occupate==0){
                    root=malloc(sizeof(struct node)*(ind2+1));
                }
                else {
                    root = realloc(root, (ind2 + 1) * sizeof(struct node));
                }
                size = ind2 + 1;

                last->instance=root;
                occupate = ind2;
                last->occ=occupate;
            }
            /* printf("Stack:\n");
             for(i=0; i<dimStack; i++)
                 if(*(stack+i))
                     printf("%d. %s", i, *(stack+i));
                 else
                     printf("%d. NULL\n", i);*/
            //oldocc=dimStack;
            dimStack+=ind2-ind1+1;
            //printf("maxStack: %d\ndimStack: %d\n", maxStack, dimStack);
            //printf("ind2-ind1+1=%d\n",ind2-ind1+1);
            maxStack+=ind2-ind1+1;

            stack=realloc(stack, sizeof(char *)*(maxStack+1));

            sp=dimStack;
            //printf("occupate: %d\n", occupate);
            for (i = ind1, k=0; i <= ind2; i++, k++) {
                //printf("giro %d\n",i );
                fgets(line, MAX, stdin);
                j = strlen(line);
                linea =  calloc(1, j + 1);
                strncpy(linea, line, j + 1);

                if(root && root[i].mod==1) {//salvo nello stack root[i]
                    *(stack+oldocc+k)=root[i].riga;

                }
                else{//salvo nello stack NULL
                    //printf("salvo NULL\n");

                    *(stack+oldocc+k)=NULL;
                }

                root[i].riga= linea;
                root[i].mod=1;
                //printf("immetto riga[%d]: %s\n", i, linea);

            }
            fgets(line, MAX, stdin);
            nIstr++;
            maxIstr++;
        }

        if(mode=='p') {
            i=-1;
            for (i = ind1; i<1; i++)
                printf(".\n");
            if(i==-1)
                i=ind1;
            for ( ;i <= ind2 && i <= occupate; i++) {
                //printf("giro i=%d\n", i);
                printf("%s", root[i].riga);
            }
            for (; i <= ind2; i++)
                printf(".\n");

        }

        if(mode=='d'){
            int putNull=0; //flag: se ho ind1<occupate<ind2 devo cancellare tutto
            int putAll=0; //flag: se ho ind1>occupate || ind2>occupate devo appendere root
            //printf("metto in stack: %s", linea);
            //printf("occupate: %d\n", occupate);
            if(nUndo>0) {
                setZero=1;
                nUndo=0;
                //nIstr--;
            }
            if(nIstr>=elements){
                elements+=E;
                occArr=realloc(occArr, sizeof(int)*elements);
            }
            undo[nIstr].i1=ind1;
            undo[nIstr].i2=ind2;
            undo[nIstr].m='d';
            *(occArr+nIstr)=occupate;
            shift=-1;

            if(ind1<=occupate && ind2>=occupate)//ossia cancello tutto
                putNull=1;
            if(ind1>occupate || ind2==0)
                putAll=1;
            //printf("putAll=%d\n", putAll);
            if(ind1<=0)
                ind1=1;
            if(ind2==0)
                ind2=0;
            if(ind2>occupate) {
                ind2 = occupate;
                last->occ=occupate;
            }
            shift = ind2 - ind1 + 1;
            //printf("shift: %d\n", shift);
            temp =calloc((occupate-shift+1), sizeof(struct node));
            for (i = 1, j = 1; i < ind1 && i<=occupate; i++, j++) {
                //printf("a. giro %d\n", i);
                temp[j].riga = root[i].riga;
                temp[j].mod=root[i].mod;
                //printf("a.copio root[%d].riga: %sin temp[%d].riga: %s", i, root[i].riga, i, temp[i].riga);
            }
            for (i = ind2+1 ; i <= occupate; i++, j++) {
                //printf("b. giro %d\n", i);
                temp[j].riga = root[i].riga;
                temp[j].mod=root[i].mod;
                //printf("b.temp[%d].riga = root[%d].riga: %s",j, i, root[i].riga);
            }
            //for(i=1; i<=occupate; i++)
            //printf("%d. %s", i, root[i].riga);

            last->occ=occupate;
            //printf("salvo %d occupate dopo %s", occupate, linea);
            if(shift>=0)
                occupate=occupate-shift;
            if(occupate<0)
                occupate=0;
            //printf("occupate=%d\n", occupate);
            if(putAll==1)
                append(&head, last, root);
            else {
                append(&head, last, temp);
            }
            last=last->next;
            last->occ=occupate;
            root=last->instance;
            //for(i=1; i<=occupate; i++)
            //  printf("%d.mod=%d %s", i, root[i].mod, root[i].riga);
            nIstr++;
            maxIstr++;
        }

        if(mode=='u' || mode == 'r'){
            //printf("1. nUndo: %d\n", nUndo);

            int r=nUndo, u=nIstr;
            doU=1;
            if(mode=='u'){
                if(ind1>nIstr)
                    ind1=nIstr;
            }
            else{
                if(ind1>nUndo)
                    ind1=nUndo;
                ind1=-ind1;
            }
            r+=ind1;
            u-=ind1;
            do {
                readfromline=0;
                fgets(lineBuffer, MAX, stdin);
                string = strdup(lineBuffer);
                found = strsep(&string, ",");
                ind12 = atoi(found);
                found = strsep(&string, ",");
                for (i = 0; lineBuffer[i] != '\n'; i++);
                mode = lineBuffer[i - 1];
                if(mode=='u') {
                    ind1+=ind12;
                    if(ind1>nIstr){
                        ind1=nIstr;
                        r=nIstr;
                        u=0;
                    }
                    else {
                        r += ind12;
                        u -= ind12;
                    }
                }
                if(mode=='r') {
                    ind1 -= ind12;
                    if(-ind1>nUndo) {
                        ind1 = -nUndo;
                        r=0;
                        u=nIstr+nUndo;
                    }
                    else {
                        r -= ind12;
                        u += ind12;
                    }
                }
            } while(mode=='u' || mode=='r');
            //printf("2. nUndo: %d\n", nUndo);
            //printf("esco con lineB: %s", lineBuffer);
            //printf("undoDisp=%d, indR=%d, indU=%d\n", undoDisp, indR, indU);
            // se ind1<0 faccio redo, però lo faccio solo se nUndo>=ind1

            if(ind1<0){
                doU=0;
                ind1=-ind1;
                if(ind1>nUndo)
                    ind1=nUndo;
            }
            else {
                //printf("a. nUndo: %d\n", nUndo);
                doU=1;

            }
            if(nUndo<0)
                nUndo=0;
            if(doU==1) {
                roll=1;
                if (nIstr < ind1) {
                    ind1 = nIstr;
                    //printf("ok: ind1=%d\n", ind1);
                }

                //printf("faccio %du\n", ind1);
                for (i = 0; i < ind1 && nIstr>=0; i++) {
                    ind11=undo[nIstr-1].i1;
                    ind22=undo[nIstr-1].i2;
                    mode=undo[nIstr-1].m;
                    t=occupate;
                    // printf("%d. undo di %d,%d%c\n",i, ind11, ind22, mode);
                    if (mode == 'c') {
                        //printf("sp=%d\n", sp);
                        /*printf("Stack:\n");
                        for(j=0; j<dimStack; j++)
                            if(*(stack+j))
                                printf("%d. %s", j, *(stack+j));
                            else
                                printf("%d. NULL\n", j);*/
                        occupate=*(occArr+nIstr-1);
                        //printf("al giro %d faccio %c\n", i, mode);
                        //printf("nIstr=%d\n", nIstr);
                        //printf("*(occArr+nIstr-1)=%d\n", *(occArr+nIstr-1));
                        if(ind11==occupate+1){//se ho semplicemente "appeso" nell'ultima istruzione i.e. occupate prima = 2, ind11 = 3 (tipo 3,5c)
                            //devo solo ridimensionare root dopo aver salvato nello stack ciò che c'è dentro root in queste posizioni
                            //printf("ok\n");
                            for(j=ind11, k=sp-(ind22-ind11+1); j<=ind22; j++, k++){
                                *(stack+k)=root[j].riga;
                                root[j].riga=NULL;
                            }
                            //printf("occupate: %d\n", occupate);
                            //root=realloc(root, (occupate) * sizeof(struct node));
                            //printf("ok\n");
                            //sp--;
                        }
                        else{//ind11 è "dentro" root; posso comunque aver appeso
                            //printf("occupate: %d\n", occupate);
                            //printf("sp=%d\n", sp);
                            for(h=1, j=ind11, k=sp-(ind22-ind11+1); k<=sp && j<=ind22;h++, k++, j++){
                                //printf("j=%d, ind22=%d, k=%d, sp=%d\n", j, ind22, k , sp);
                                string=*(stack+k);
                                //printf("string: %s", string);
                                //printf("root: %s", root[j].riga);
                                if(j<=t) {
                                    //printf("rimetto in root %s", string);
                                    *(stack + k) = root[j].riga;
                                    root[j].riga = string;
                                }
                                else{
                                    //printf("ok\n");
                                    if(j<=t){
                                        *(stack+k)=root[j].riga;

                                    }
                                    else {
                                        *(stack + k) = NULL;

                                    }
                                }
                            }
                            last->instance=root;
                            last->occ=occupate;
                        }
                        sp-=(ind22-ind11+1);
                        //root=realloc(root, (occupate+1) * sizeof(struct node));

                    } else //delete
                    {
                        //printf("al giro %d faccio %c\n", i, mode);
                        //occupate = last->occ;
                        //printf("ok\n");

                        last = last->prev;
                        root = last->instance;
                        occupate = last->occ;
                        /*for(j=1; j<=occupate; j++)
                          printf("%d.mod=%d %s", j, root[j].mod, root[j].riga);
                        printf("occ: %d\n", last->occ);*/



                    }
                    //for(j=1; j<=occupate; j++)
                    //  printf("%d.mod=%d %s", j, root[j].mod, root[j].riga);
                    *(occArr+nIstr-1)=t;
                    nIstr--;
                    nUndo++;
                    //printf("occupate: %d\n", occupate);
                }

            }
            else{//faccio redo
                roll=1;
                //if(ind1>nUndo)
                //  ind1=nUndo;
                //printf("nUndo=%d\n", nUndo);
                //printf("faccio %dr\n", ind1);
                for (i = 0; i < ind1 && nIstr<maxIstr; i++) {
                    //printf("nistr: %d\n", nIstr);
                    //printf("occupate: %d\n", occupate);
                    ind11=undo[nIstr].i1;
                    ind22=undo[nIstr].i2;
                    mode=undo[nIstr].m;
                    //printf("a %d faccio %d,%d%c\n", i, ind11, ind22, mode);
                    t=occupate;
                    occupate=*(occArr+nIstr);
                    if (mode == 'c') {
                        //printf("occupate: %d, ind22 : %d, nIstr=%d\n", occupate, ind22, nIstr);
                        if(occupate<ind22){
                            //printf("occupate: %d\n", occupate);
                            //printf("realloc!!!!\n");
                            //root = realloc(root, (ind22+1) * sizeof(struct node));
                            last->instance=root;
                            occupate = ind22;
                            last->occ=occupate;
                        }
                        //printf("sp: %d, occupate=%d\n", sp, occupate);
                        for (j = ind11, k=sp; j <= ind22 && k<sp+(ind22-ind11+1); j++, k++, sp++) {
                            linea = *(stack+k);
                            //printf("salvo dentro stack[%d]: ", k);
                            //printf("giro %d, linea %s",j ,linea);
                            if(j<=t && root && root[j].mod==1) {//salvo nello stack root[i]
                                *(stack+k)=root[j].riga;
                                //printf("ok, giro: %d\n", j);
                                //printf("%s", root[j].riga);
                            }
                            else{//salvo nello stack NULL
                                *(stack+k)=NULL;
                                //printf("NULL\n");
                            }
                            root[j].riga= linea;
                            root[j].mod=1;
                            //printf("immetto riga[%d]: %s\n", i, linea);

                        }
                        last->instance=root;
                        last->occ=occupate;
                        sp=k;
                    } else//redo di delete
                    {
                        //printf("a %d faccio %c\n", i, mode);
                        //printf("%dr\n", i);
                        if(last) {
                            last = last->next;
                            //occupate=last->occ;

                            root = last->instance;

                        }
                        //for(k=1; k<=occupate; k++)
                        // printf("%d/%d %s", k, occupate, root[k].riga);

                    }
                    *(occArr+nIstr)=t;
                    //printf("ok\n");
                    nIstr++;
                    nUndo--;
                    //printf("occupate: %d\n", occupate);
                }
                //nIstr++;
                //printf("ok\n");
            }
            if(nIstr<0)
                nIstr=0;
            //printf("nUndo: %d\n", nUndo);
        }
        //printf("occupate:%d\n", occupate);
        /* for(i=1; i<=occupate; i++)
              printf("%d.mod=%d %s", i, root[i].mod, root[i].riga);*/

        if(readfromline==1)
            fgets(line, MAX, stdin);
        else
        {
            //printf("ok eseguo: %s", lineBuffer);
            strcpy(line, lineBuffer);
            readfromline=1;
        }
        // printf("nIstr=%d\n", nIstr);
        /*printf("undo:\n");
        for(i=0; i<nIstr; i++){
            printf("%d. %s", i, *(undo+i));
        }*/
        /* printf("occArr:\n");
         for(i=0; i<5; i++)
             printf("%d. %d\n", i, *(occArr+i));*/
        //printf("sp: %d\n", sp);
        // printf("Stack:\n");
        /*for(i=0; i<dimStack; i++)
            if(*(stack+i))
                printf("%d. %s", i, *(stack+i));
            else
                printf("%d. NULL\n", i);*/
        //printf("nUndo=%d\n", nUndo);
    }
    //dealloco tutte le istanze

    /*while((new=head)!=NULL){
        head=head->next;
        //free(new->instance);
        free(new);
    }*/
    //deallocastack(undo);
    //deallocastack(redo);
    return;
}
