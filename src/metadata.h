void insert(char *filename);
void update(char *filename);
void delete(char *filename);
void print_dataField(char *filename);


int menu(void){
	int ans;
	printf("%s\n%s\n%s\n%s\n%s\n: ", "1. Inserir registro", "2. Atualizar campo de registro",
		"3. Remover registro", "4. Mostrar registros", "5. Finalizar aplicação");
	scanf("\n%d", &ans);

	return ans;
}