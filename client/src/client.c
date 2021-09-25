#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();

	log_info(logger, "Soy un log");

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'
	config_set_value(config, "valor", CLAVE);
	config_set_value(config, "ip", ip);
	config_set_value(config, "puerto", puerto);


	config_save(config);

	//Loggeamos el valor de config

	log_info(logger, config_get_string_value(config, "valor"));

	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor, conexion);
	// Armamos y enviamos el paquete
	paquete(conexion);
	char* mensaje;
	while(1){
		mensaje = readline("Mensaje > ");
		if(string_is_empty(mensaje)){
			free(mensaje);
			break;
		}
		enviar_mensaje(mensaje, conexion);
		free(mensaje);
	}

		size = strlen(mensaje_paquete)+1;
		agregar_a_paquete(paquete, mensaje_paquete, size);
		free(mensaje_paquete);
	}

	//Enviamos paquete y liberamos
	enviar_paquete(paquete, conexion);
	eliminar_paquete(paquete);


	terminar_programa(conexion, logger, config);
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;
	nuevo_logger = log_create("tp0.log", "tp0", 1, LOG_LEVEL_INFO);	

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;
	nuevo_config = config_create("tp0.config");

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
while(1){
		leido = readline("> ");
// El resto, las vamos leyendo y logueando hasta recibir un string vacío
		if(string_is_empty(leido)){
			free(leido);
			break;
		}
		log_info(logger, leido);
	// ¡No te olvides de liberar las lineas antes de regresar!
		free(leido);
	}

}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;
	paquete = crear_paquete();
	int tamanio;
	// Leemos y esta vez agregamos las lineas al paquete
	leido = readline(">");

	while (strcmp(leido, "") != 0) {
		log_info(logger, leido);
		tamanio = strlen(leido)+1;
		agregar_a_paquete(paquete, leido, tamanio);
		free(leido);
		leido = readline(">");
	}

	enviar_paquete(paquete, conexion);

	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	eliminar_paquete(paquete);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
	  	liberar_conexion(conexion);
		log_destroy(logger);
		config_destroy(config);
}
