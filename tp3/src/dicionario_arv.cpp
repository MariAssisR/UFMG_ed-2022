#include "dicionario_arv.hpp"
#include "verbete.hpp"

DicArvore::DicArvore(){
    _raiz = nullptr;
    _num = 0;
    _numVerbetesComSig = 0;
}
DicArvore::~DicArvore(){
    if(_raiz != nullptr)
        destroiDic(_raiz);
}
//retorna a altura de um no
int DicArvore::getAltura(item* no){
    if(no == nullptr)
        return 0;
    //leMemLog((long int)(&(no->_verbete)),sizeof(Verbete),0);
    return no->altura;
}
//retorna o balanceamento de um no
//balanceamento é a diferença de altura entre esquerda e direita
//na avl fica entre -1 e 1
int DicArvore::balanceamento(item* no){
    if(no == nullptr)
        return 0;
    //leMemLog((long int)(&(no->_verbete)),sizeof(Verbete),0);
    return getAltura(no->dir) - getAltura(no->esq);
}

//funções usadas para os 4 casos de rotação
item* DicArvore::rotacaoEsq(item* x){
    item *novo_pai = x->dir;
    item *y = novo_pai->esq;
    novo_pai->esq = x;
    x->dir = y;
    x->altura = MAX(getAltura(x->dir), getAltura(x->esq)) + 1;
    novo_pai->altura = MAX(getAltura(novo_pai->dir), getAltura(novo_pai->esq)) + 1;
    return novo_pai;
}
item* DicArvore::rotacaoDir(item* y){
    item *novo_pai = y->esq;
    item *x = novo_pai->dir;
    novo_pai->dir = y;
    y->esq = x;
    novo_pai->altura = MAX(getAltura(novo_pai->dir), getAltura(novo_pai->esq)) + 1;
    y->altura = MAX(getAltura(y->dir), getAltura(y->esq)) + 1;
    return novo_pai;
}
//checa o balanceamento e realiza a rotação necessaria para corrigir
item* DicArvore::balancear(item* no){
    int valor_balanceamento = balanceamento(no);
    //caso 1
    if(valor_balanceamento < -1 && strcmp(no->_verbete->nome.c_str(),no->esq->_verbete->nome.c_str())>0){
        return rotacaoDir(no);
    }
    //caso 2
    if(valor_balanceamento > 1 && strcmp(no->_verbete->nome.c_str(),no->dir->_verbete->nome.c_str())<0){
        return rotacaoEsq(no);
    }
    //caso 3
    if(valor_balanceamento < -1 && strcmp(no->_verbete->nome.c_str(),no->esq->_verbete->nome.c_str())<0){
        no->esq = rotacaoEsq(no->esq);
        return rotacaoDir(no);
    }
    //caso 4
    if(valor_balanceamento > 1 && strcmp(no->_verbete->nome.c_str(),no->dir->_verbete->nome.c_str())>0){
        no->dir = rotacaoDir(no->dir);
        return rotacaoEsq(no);
    }
    return no;
}

void DicArvore::insereDic(Verbete* it){
    _raiz = insereDicRec(_raiz,it);
}
item* DicArvore::insereDicRec(item* no,Verbete* it){
    //it é um verbete que contem tipo,nome e talvez o significado
    //add palavra NAO existente
    if(no == nullptr){
        no = new item[1];
        //escreveMemLog((long int)(&(no->_verbete)),sizeof(Verbete),0);
        no->_verbete = it;
        _num++;
        if(no->_verbete->significado.tam > 0)
            _numVerbetesComSig++;
        return no;
    }
    else if(strcmp(no->_verbete->nome.c_str(),it->nome.c_str())>0){
        //leMemLog((long int)(&(no->_verbete)),sizeof(Verbete),0);
        no->esq = insereDicRec(no->esq,it);
    }
    else if(strcmp(no->_verbete->nome.c_str(),it->nome.c_str())<0){
        //leMemLog((long int)(&(no->_verbete)),sizeof(Verbete),0);
        no->dir = insereDicRec(no->dir,it);
    }
    //add palavra existente
    else{
        //palavra "nova"
        //leMemLog((long int)(&(no->_verbete)),sizeof(Verbete),0);
        if(no->_verbete->tipo < it->tipo){
            no->dir = insereDicRec(no->dir,it);
        }
        else if(no->_verbete->tipo > it->tipo){
            no->esq = insereDicRec(no->esq,it);
        }
        //atualizar somente número de significados
        else if(it->significado.tam > 0){
            string significado_novo = it->significado.primeiro->texto;
            if(no->_verbete->significado.tam > 0)
                _numVerbetesComSig++;
            no->_verbete->significado.insereSignificado(significado_novo);
        } 
    }

    //atualizar altura
    no->altura = MAX(getAltura(no->dir), getAltura(no->esq)) + 1;
    //balancear
    return balancear(no);
}

int DicArvore::pesquisaDic(Verbete* it){
    item* aux = pesquisaDicRec(_raiz,it);
    if(aux != nullptr)
        return 1;
    else
        return 0;
}
item* DicArvore::pesquisaDicRec(item* no, Verbete* it){
    if(no == nullptr || strcmp(no->_verbete->nome.c_str(),it->nome.c_str())==0){
        //não achou
        return no;
    }
    //buscar
    else if(strcmp(no->_verbete->nome.c_str(),it->nome.c_str())>0)
        pesquisaDicRec(no->esq, it);
    else
        pesquisaDicRec(no->dir, it);
}

void DicArvore::imprimeDic(ostream &f_out){
    imprimeDicRec(_raiz, f_out);
}
void DicArvore::imprimeDicRec(item* no, ostream &f_out){
    //caminhamento in-order
    if(no != nullptr){
        //leMemLog((long int)(&(no->_verbete)),sizeof(Verbete),0);
        imprimeDicRec(no->esq,f_out);
        //imprimir verbete
        f_out << no->_verbete->nome;
        //tipo
        f_out << " (" << no->_verbete->tipo << ")" << endl;
        //significados
        no->_verbete->significado.imprimirSignificadosParaDic(f_out);
        imprimeDicRec(no->dir,f_out);
    }
}

void DicArvore::removeDic(){
    removeDicRec(_raiz);
}
void DicArvore::removeDicRec(item* &no){
    //caminhamento pos-order
    if (no == nullptr) 
        return; 
    
    //leMemLog((long int)(&(no->_verbete)),sizeof(Verbete),0);
    removeDicRec(no->esq);
    removeDicRec(no->dir);
    //se tiver algum significado
    if(no->_verbete->significado.tam > 0){
        //1 ou 0 filhos
        item *aux = no;
        if(no->dir == nullptr){
            no = no->esq;
            delete[] aux;
            _num--;
        }
        else if(no->esq == nullptr){
            no = no->dir;
            delete[] aux;
            _num--;
        }
        //tem 2 filhos, subs pelo antecessor > in-order
        else{
            antecessor(no, no->esq);
        }
    }
    if (no == nullptr) 
        return; 

    //atualizar altura
    no->altura = MAX(getAltura(no->dir), getAltura(no->esq)) + 1;
    //balancear
    no = balancear(no);
}
void DicArvore::antecessor(item* no,item* &no_prox) {
    if(no_prox->dir != nullptr){
        antecessor(no, no_prox->dir);
        return;
    }
    //leMemLog((long int)(&(no_prox->_verbete)),sizeof(Verbete),0);
    //leMemLog((long int)(&(no->_verbete)),sizeof(Verbete),0);
    no->_verbete = no_prox->_verbete;
    no = no_prox;
    no_prox = no_prox->esq;
    delete[] no;
    _num--;
}

void DicArvore::destroiDic(item* &no){
    //caminhamento pos-order
    if (no != nullptr){
        destroiDic(no->esq);
        destroiDic(no->dir);
        delete[] no;
    }
}
