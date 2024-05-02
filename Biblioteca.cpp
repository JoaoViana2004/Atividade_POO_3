#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::remove_if; 

using std::cout;
using std::cin;
using std::endl;

class Autor{
    string nome;

    public:

        Autor(const string n):nome(n){};
        ~Autor(){};
        string get_nome(){return nome;};
        void set_nome(const string n){nome = n;};

        void print_info(){
            cout<<"Autor : "<<nome<<" ;"<<endl;
        }
};

class Livro{
    string titulo;
    vector<Autor*> autores;
    int n_paginas;

    public: 

    Livro(const string t, int p):titulo(t), n_paginas(p){};
    ~Livro(){};

    string get_titulo(){return titulo;};
    void set_titulo(const string n){titulo = n;};
    int get_n_paginas(){return n_paginas;};
    void set_n_paginas(const int n){n_paginas = n;};

    void print_info(){
            cout<<"Livro : "<<titulo<<" ;"<<endl;
            cout<<"Autores : "<<endl;
            for(Autor* aut : autores){
                aut->print_info();
            }
            cout<<"Numero de Paginas: "<<n_paginas<<endl;
            tipo();
        }
    
    vector<Autor*> get_autores(){return autores;};

    void operator+(Autor& aut){
        autores.push_back(&aut);
    };
    void operator-(Autor& aut){
        autores.erase(std::remove(autores.begin(), autores.end(), &aut), autores.end());
    };

    virtual void tipo() = 0;
};

class LivroFisico:public Livro{
    string tipo_papel;

    public:

    LivroFisico(const string t, int p, string tipo):Livro(t,p),tipo_papel(tipo){};

    void tipo(){cout<<"Tipo: FISICO;"<<endl<<"Tipo de papel: "<<tipo_papel<<";"<<endl;}
    
};

class LivroDigital:public Livro{
    string tipo_documento;

    public:

    LivroDigital(const string t, int p, string tipo):Livro(t,p),tipo_documento(tipo){};

    void tipo(){cout<<"Tipo: DIGITAL;"<<endl<<"Formato: "<<tipo_documento<<";"<<endl;}
    
};

class Biblioteca{
    vector<Livro*> livros;
    
    public:

    Biblioteca(){};
    ~Biblioteca(){};

    void adicionar_livro(Livro* l){livros.push_back(l);};
    void remover_livro(Livro* l){ livros.erase(std::remove(livros.begin(), livros.end(), l), livros.end());};
    void remover_livro(const string& tituloLivro) {
        auto it = std::find_if(livros.begin(), livros.end(), [&](Livro* l) { return l->get_titulo() == tituloLivro; });

        if (it != livros.end()) {
            delete *it; // Liberar a memória alocada para o livro
            livros.erase(it); // Remover o livro da lista
            cout << "Livro removido com sucesso!" << endl;
        } else {
            cout << "Livro nao encontrado na biblioteca." << endl;
        }
    }
    void print_info(){
            cout<<"Livros : "<<endl;
            for(Livro* l : livros){
                l->print_info();
                cout<<endl;
            }
        }
    
    void operator+(Livro& book){
        adicionar_livro(&book);
    };
    void operator-(Livro& book){
        remover_livro(&book);    
    };
};

void exibir_menu() {
    cout<<endl;
    cout << "MENU Biblioteca:" << endl;
    cout << "1. Criar Livro" << endl;
    cout << "2. Excluir Livro" << endl;
    cout << "3. Criar Autor" << endl;
    cout << "4. Excluir Autor" << endl;
    cout << "5. Adicionar Autor ao Livro" << endl;
    cout << "6. Adicionar Livro à Biblioteca" << endl;
    cout << "7. Remover Livro da Biblioteca" << endl;
    cout << "8. Lista Livros na Biblioteca" << endl;
    cout << "0. Sair" << endl;
    cout<<endl;
};


int main(){

    int opcao;
    Biblioteca biblioteca;

    vector<LivroDigital*> livros_digital;
    vector<LivroFisico*> livros_fisico;
    vector<Autor*> autores;

    do {
        exibir_menu();
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1: {
    string titulo;
    string tipo_l;
    int paginas;
    int tipo;

    cout << "Digite o titulo do livro: ";
    cin.ignore(); // Limpar o buffer de entrada
    getline(cin, titulo);
    cout << "Digite o numero de paginas: ";
    cin >> paginas;
    cout<<"O livro é digital ? (1/SIM): ";
    cin>>tipo;

    cout<<endl<<"Defina o tipo do Documento: ";
    cin.ignore(); // Limpar o buffer de entrada
    getline(cin, tipo_l);

    if(tipo){
        livros_digital.push_back(new LivroDigital(titulo, paginas, tipo_l));
    }else{
        livros_fisico.push_back(new LivroFisico(titulo, paginas, tipo_l));
    }

    cout << "Livro criado com sucesso!" << endl;
    break;
}
case 2:{
    string titulo;
    int tipo;

    cout<<"O livro eh digital ? (1/SIM): ";
    cin>>tipo;

    if(tipo == 1){
        for (auto it = livros_digital.begin(); it != livros_digital.end(); ++it){
            if((*it)->get_titulo() == titulo){
                delete *it;
                livros_digital.erase(it);
                cout<<"Livro excluido com Sucesso"<<endl;
                break;
            }
        
        }
    }else{
        for (auto it = livros_fisico.begin(); it != livros_fisico.end(); ++it){
            if((*it)->get_titulo() == titulo){
                delete *it;
                livros_fisico.erase(it);
                cout<<"Livro excluido com Sucesso"<<endl;
                break;
            }
        
        }
    }

    break;
}
case 3: {
    string nome;
    cout << "Digite o nome do autor: ";
    cin.ignore(); // Limpar o buffer de entrada
    getline(cin, nome);
    cout << "Autor criado com sucesso!" << endl;
    autores.push_back(new Autor(nome));
    break;
}
case 4: {
    string nome;
    cout << "Digite o nome do autor que deseja excluir: ";
    cin.ignore(); // Limpar o buffer de entrada
    getline(cin, nome);

    auto it = std::find_if(autores.begin(), autores.end(), [&](Autor* a) { return a->get_nome() == nome; });

    if (it != autores.end()) {
        delete *it;
        autores.erase(it);
        cout << "Autor excluido com sucesso!" << endl;
    } else {
        cout << "Autor nao encontrado." << endl;
    }
    break;
}
case 5: {
    string nomeAutor, tituloLivro;
    cout << "Digite o nome do autor: ";
    cin.ignore(); // Limpar o buffer de entrada
    getline(cin, nomeAutor);

    cout << "Digite o titulo do livro: ";
    getline(cin, tituloLivro);

    Autor* autor = nullptr;
    Livro* livro = nullptr;

    // Encontrar o autor e o livro
    for (Autor* a : autores) {
        if (a->get_nome() == nomeAutor) {
            autor = a;
            break;
        }
    }

    if (!autor) {
        cout << "Autor nao encontrado." << endl;
        break;
    }

    for (Livro* l : livros_digital) {
        if (l->get_titulo() == tituloLivro) {
            livro = l;
            break;
        }
    }

    for (Livro* l : livros_fisico) {
        if (l->get_titulo() == tituloLivro) {
            livro = l;
            break;
        }
    }

    if (!livro) {
        cout << "Livro nao encontrado." << endl;
        break;
    }

    *livro + *autor;
    cout << "Autor adicionado ao livro com sucesso!" << endl;
    break;
}
case 6: {
    string tituloLivro;
    int tipo;

    cout << "Digite o titulo do livro que deseja adicionar: ";
    cin.ignore(); // Limpar o buffer de entrada
    getline(cin, tituloLivro);

    cout << "O livro eh digital ? (1/SIM): ";
    cin >> tipo;

    Livro* livro = nullptr;

    if (tipo == 1) {
        for (LivroDigital* l : livros_digital) {
            if (l->get_titulo() == tituloLivro) {
                livro = l;
                break;
            }
        }
    } else {
        for (LivroFisico* l : livros_fisico) {
            if (l->get_titulo() == tituloLivro) {
                livro = l;
                break;
            }
        }
    }

    if (!livro) {
        cout << "Livro nao encontrado." << endl;
        break;
    }

    biblioteca + *livro;
    cout << "Livro adicionado à biblioteca com sucesso!" << endl;
    break;
}
case 7: {
    string tituloLivro;
    cout << "Digite o titulo do livro que deseja remover: ";
    cin.ignore(); // Limpar o buffer de entrada
    getline(cin, tituloLivro);

    biblioteca.remover_livro(tituloLivro);
    break;
}
case 8:{
    biblioteca.print_info();
    break;
}


            case 0: {
                cout << "Saindo do programa..." << endl;
                break;
            }
            default:
                cout << "Opcao invalida! Tente novamente." << endl;
        }

    } while (opcao != 0);

    return 0;
}