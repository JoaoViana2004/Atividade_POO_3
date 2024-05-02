#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
// Inclusão de bibliotecas necessárias.

using std::string;
using std::vector;
using std::remove_if; 
// Declaração do uso do namespace std para evitar repetição do prefixo std::.

using std::cout;
using std::cin;
using std::endl;
// Declaração do uso específico dos objetos cout, cin e endl do namespace std.

class Autor{
    string nome; // Nome do autor.

    public:
        Autor(const string n):nome(n){}; // Construtor que inicializa o nome do autor.
        ~Autor(){}; // Destrutor padrão.
        string get_nome(){return nome;}; // Método para retornar o nome do autor.
        void set_nome(const string n){nome = n;}; // Método para definir o nome do autor.

        void print_info(){ // Método para imprimir as informações do autor.
            cout<<"Autor : "<<nome<<" ;"<<endl;
        }
};

class Livro{
    string titulo; // Título do livro.
    vector<Autor*> autores; // Vetor de ponteiros para autores associados ao livro.
    int n_paginas; // Número de páginas do livro.

    public: 
    Livro(const string t, int p):titulo(t), n_paginas(p){}; // Construtor que inicializa o título e número de páginas do livro.
    ~Livro(){
        // Desalocando a memória manualmente
        for (Autor* ptr : autores) {
            delete ptr;
        }

        // Limpando o vetor
        autores.clear();

    }; // Destrutor padrão.

    string get_titulo(){return titulo;}; // Método para retornar o título do livro.
    void set_titulo(const string n){titulo = n;}; // Método para definir o título do livro.
    int get_n_paginas(){return n_paginas;}; // Método para retornar o número de páginas do livro.
    void set_n_paginas(const int n){n_paginas = n;}; // Método para definir o número de páginas do livro.

    void print_info(){ // Método para imprimir as informações do livro.
            cout<<"Livro : "<<titulo<<" ;"<<endl; // Imprime o título do livro.
            cout<<"Autores : "<<endl; // Imprime os autores associados ao livro.
            for(Autor* aut : autores){ // Percorre o vetor de autores.
                aut->print_info(); // Imprime as informações de cada autor.
            }
            cout<<"Numero de Paginas: "<<n_paginas<<endl; // Imprime o número de páginas do livro.
            tipo(); // Chama o método tipo() da classe Livro.
        }
    
    vector<Autor*> get_autores(){return autores;}; // Método para retornar o vetor de autores associados ao livro.

    void operator+(Autor& aut){ // Sobrecarga do operador + para adicionar um autor ao livro.
        autores.push_back(&aut); // Adiciona um ponteiro para o autor ao vetor de autores do livro.
    };
    void operator-(Autor& aut){ // Sobrecarga do operador - para remover um autor do livro.
        autores.erase(std::remove(autores.begin(), autores.end(), &aut), autores.end()); // Remove o autor do vetor de autores do livro.
    };

    virtual void tipo() = 0; // Método virtual puro para definir o tipo do livro.
};

class LivroFisico:public Livro{ // Classe derivada de Livro para representar um livro físico.
    string tipo_papel; // Tipo de papel do livro físico.

    public:
    LivroFisico(const string t, int p, string tipo):Livro(t,p),tipo_papel(tipo){}; // Construtor que inicializa o título, número de páginas e tipo de papel do livro físico.

    void tipo(){cout<<"Tipo: FISICO;"<<endl<<"Tipo de papel: "<<tipo_papel<<";"<<endl;} // Implementação do método tipo() para livros físicos.
    
};

class LivroDigital:public Livro{ // Classe derivada de Livro para representar um livro digital.
    string tipo_documento; // Tipo de documento do livro digital.

    public:
    LivroDigital(const string t, int p, string tipo):Livro(t,p),tipo_documento(tipo){}; // Construtor que inicializa o título, número de páginas e tipo de documento do livro digital.

    void tipo(){cout<<"Tipo: DIGITAL;"<<endl<<"Formato: "<<tipo_documento<<";"<<endl;} // Implementação do método tipo() para livros digitais.
    
};

class Biblioteca{
    vector<Livro*> livros; // Vetor de ponteiros para livros na biblioteca.
    
    public:
    Biblioteca(){}; // Construtor padrão.
    ~Biblioteca(){
                // Desalocando a memória manualmente
                for (Livro* ptr : livros) {
                    delete ptr;
                }

                // Limpando o vetor
                livros.clear();
    }; // Destrutor padrão.

    void adicionar_livro(Livro* l){livros.push_back(l);}; // Método para adicionar um livro à biblioteca.
    void remover_livro(Livro* l){ livros.erase(std::remove(livros.begin(), livros.end(), l), livros.end());}; // Método para remover um livro da biblioteca.
    void remover_livro(const string& tituloLivro) { // Método para remover um livro da biblioteca pelo título.
        auto it = std::find_if(livros.begin(), livros.end(), [&](Livro* l) { return l->get_titulo() == tituloLivro; }); // Procura o livro pelo título.

        if (it != livros.end()) { // Se o livro for encontrado.
            delete *it; // Libera a memória alocada para o livro.
            livros.erase(it); // Remove o livro do vetor.
            cout << "Livro removido com sucesso!" << endl; // Informa que o livro foi removido com sucesso.
        } else { // Se o livro não for encontrado.
            cout << "Livro nao encontrado na biblioteca." << endl; // Informa que o livro não foi encontrado na biblioteca.
        }
    }
    void print_info(){ // Método para imprimir as informações dos livros na biblioteca.
            cout<<"Livros : "<<endl; // Imprime a lista de livros na biblioteca.
            for(Livro* l : livros){ // Percorre o vetor de livros.
                l->print_info(); // Imprime as informações de cada livro.
                cout<<endl; // Adiciona uma linha em branco entre os livros.
            }
        }
    
    void operator+(Livro& book){ // Sobrecarga do operador + para adicionar um livro à biblioteca.
        adicionar_livro(&book); // Chama o método adicionar_livro() para adicionar o livro à biblioteca.
    };
    void operator-(Livro& book){ // Sobrecarga do operador - para remover um livro da biblioteca.
        remover_livro(&book); // Chama o método remover_livro() para remover o livro da biblioteca.
    };
};

void exibir_menu() { // Função para exibir o menu da biblioteca.
    cout<<endl; // Adiciona uma linha em branco antes do menu.
    cout << "MENU Biblioteca:" << endl; // Imprime o título do menu.
    cout << "1. Criar Livro" << endl; // Opção para criar um livro.
    cout << "2. Excluir Livro" << endl; // Opção para excluir um livro.
    cout << "3. Criar Autor" << endl; // Opção para criar um autor.
    cout << "4. Excluir Autor" << endl; // Opção para excluir um autor.
    cout << "5. Adicionar Autor ao Livro" << endl; // Opção para adicionar um autor a um livro.
    cout << "6. Adicionar Livro à Biblioteca" << endl; // Opção para adicionar um livro à biblioteca.
    cout << "7. Remover Livro da Biblioteca" << endl; // Opção para remover um livro da biblioteca.
    cout << "8. Lista Livros na Biblioteca" << endl; // Opção para listar os livros na biblioteca.
    cout << "0. Sair" << endl; // Opção para sair do programa.
    cout<<endl; // Adiciona uma linha em branco após o menu.
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
