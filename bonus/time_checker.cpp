#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <chrono>

int main() {
    // Création du socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Erreur lors de la création du socket" << std::endl;
        return -1;
    }

    // Configuration de l'adresse du serveur
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(4242);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connexion au serveur
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Erreur lors de la connexion au serveur" << std::endl;
        close(sock);
        return -1;
    }

    std::cout << "Connecté au serveur 127.0.0.1:4242" << std::endl;

    char buffer[1024];
    
    // 1. Attendre le message "WELCOME\n"
    std::cout << "En attente du message WELCOME..." << std::endl;
    int bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        std::cout << "Reçu: " << buffer;
        
        // Vérifier si c'est bien "WELCOME\n"
        if (std::string(buffer) == "WELCOME\n") {
            std::cout << "Message WELCOME reçu!" << std::endl;
        }
    }

    // 2. Envoyer "name1\n"
    std::string name_msg = "name1\n";
    send(sock, name_msg.c_str(), name_msg.length(), 0);
    std::cout << "Envoyé: " << name_msg;

    // 3. Attendre n'importe quel message
    std::cout << "En attente d'un autre message..." << std::endl;
    bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        std::cout << "Reçu: " << buffer;
    }

    // 4. Sauvegarder le temps et envoyer "Forward\n"
    auto start_time = std::chrono::high_resolution_clock::now();
    
    std::string forward_msg = "Forward\n";
    send(sock, forward_msg.c_str(), forward_msg.length(), 0);
    send(sock, forward_msg.c_str(), forward_msg.length(), 0);
    std::cout << "Envoyé 2 fois: " << forward_msg;
    std::cout << "Chrono démarré..." << std::endl;

    // 5. Attendre la réponse et arrêter le chrono
    std::cout << "En attente de la réponse 1 ..." << std::endl;
    bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0);
    
    auto end_time = std::chrono::high_resolution_clock::now();
    
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        std::cout << "Réponse reçue: " << buffer;
        
        // Calculer le temps écoulé en secondes
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        double seconds = duration.count() / 1000000.0;
        
        std::cout << "Temps de réponse: " << seconds << " secondes" << std::endl;
    }

    // 5. Attendre la réponse et arrêter le chrono
    std::cout << "En attente de la réponse 2..." << std::endl;
    bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0);

    end_time = std::chrono::high_resolution_clock::now();

    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        std::cout << "Réponse reçue: " << buffer;

        // Calculer le temps écoulé en secondes
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        double seconds = duration.count() / 1000000.0;

        std::cout << "Temps de réponse: " << seconds << " secondes" << std::endl;
    }

    std::cout << "Attente de la mort..." << std::endl;
    bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0);

    end_time = std::chrono::high_resolution_clock::now();

    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        std::cout << "Réponse reçue: " << buffer;

        // Calculer le temps écoulé en secondes
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        double seconds = duration.count() / 1000000.0;

        std::cout << "Temps de réponse: " << seconds << " secondes" << std::endl;
    }

    // Fermer la connexion
    close(sock);
    std::cout << "Connexion fermée." << std::endl;

    return 0;
}
