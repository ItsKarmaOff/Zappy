#!/bin/bash

# Script de lancement automatique pour Zappy avec valeurs aléatoires

# Couleurs pour l'affichage
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Fonction pour afficher les messages colorés
log_info() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

log_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

log_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

log_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Génération de valeurs aléatoires
generate_random_port() {
    echo $((RANDOM % 10000 + 5000))  # Port entre 5000 et 15000
}

generate_random_dimension() {
    echo $((RANDOM % 20 + 10))  # Dimension entre 10 et 30
}

generate_random_clients() {
    echo $((RANDOM % 5 + 2))  # Nombre de clients entre 2 et 6
}

generate_random_freq() {
    echo $((RANDOM % 90 + 10))  # Fréquence entre 10 et 100
}

# Noms d'équipes possibles
TEAM_NAMES=("Alpha" "Beta" "Gamma" "Delta" "Epsilon" "Zeta" "Eta" "Theta")

# Génération des paramètres aléatoires
PORT=4040
WIDTH=10
HEIGHT=10
CLIENTS_NB=$(generate_random_clients)
FREQ=1 # Fréquence fixe à 1 pour simplifier

# Sélection aléatoire de 2-4 équipes
NUM_TEAMS=$((RANDOM % 3 + 2))  # Entre 2 et 4 équipes
SELECTED_TEAMS=()

# Mélanger et sélectionner les équipes
shuffled_teams=($(printf "%s\n" "${TEAM_NAMES[@]}" | shuf))
for ((i=0; i<NUM_TEAMS; i++)); do
    SELECTED_TEAMS+=("${shuffled_teams[i]}")
done

# Construction de la chaîne des noms d'équipes
TEAM_STRING=""
for team in "${SELECTED_TEAMS[@]}"; do
    TEAM_STRING+=" $team"
done

echo "=========================================="
echo "    ZAPPY LAUNCHER - Valeurs aléatoires"
echo "=========================================="
echo ""
log_info "Paramètres générés :"
echo "  Port: $PORT"
echo "  Largeur: $WIDTH"
echo "  Hauteur: $HEIGHT"
echo "  Équipes:$TEAM_STRING"
echo "  Clients par équipe: $CLIENTS_NB"
echo "  Fréquence: $FREQ"
echo ""

# Vérification de l'existence des binaires
log_info "Vérification des binaires..."

if [ ! -f "./zappy_server" ]; then
    log_error "zappy_server introuvable !"
    exit 1
fi

if [ ! -f "./zappy_gui" ]; then
    log_error "zappy_gui introuvable !"
    exit 1
fi

if [ ! -f "./zappy_ai" ]; then
    log_error "zappy_ai introuvable !"
    exit 1
fi

log_success "Tous les binaires sont présents"
echo ""

# Fonction de nettoyage
cleanup() {
    log_warning "Arrêt des processus..."
    jobs -p | xargs -r kill
    exit 0
}

# Capturer Ctrl+C pour nettoyer proprement
trap cleanup SIGINT SIGTERM

# Lancement du serveur
log_info "Lancement du serveur..."
SERVER_CMD="./linux/zappy_server -p $PORT -x $WIDTH -y $HEIGHT -n$TEAM_STRING -c $CLIENTS_NB -f $FREQ"
echo "Commande: $SERVER_CMD"
$SERVER_CMD &
SERVER_PID=$!

# Attendre que le serveur soit prêt
sleep 2

# Vérifier si le serveur est toujours en vie
if ! kill -0 $SERVER_PID 2>/dev/null; then
    log_error "Le serveur a échoué au démarrage"
    exit 1
fi

log_success "Serveur lancé (PID: $SERVER_PID)"
echo ""

# Lancement des clients IA (un par équipe)
AI_PIDS=()
log_info "Lancement des clients IA..."

for team in "${SELECTED_TEAMS[@]}"; do
    # Lancer quelques IA pour cette équipe (1-3 par équipe)
    num_ai_for_team=$((RANDOM % 3 + 1))

    for ((j=1; j<=num_ai_for_team; j++)); do
        log_info "Lancement IA $j pour équipe $team"
        (echo -e "$team"; sleep 3600) | netcat localhost $PORT &
        AI_PID=$!
        AI_PIDS+=($AI_PID)
        sleep 0.5
    done
done


log_success "Toutes les IA sont lancées"
echo ""

# Affichage des informations de connexion
echo "=========================================="
echo "           INFORMATIONS DE JEU"
echo "=========================================="
echo "Port du serveur: $PORT"
echo "Taille du monde: ${WIDTH}x${HEIGHT}"
echo "Équipes actives:$TEAM_STRING"
echo "Clients par équipe: $CLIENTS_NB"
echo "Fréquence: $FREQ"
echo ""
echo "Pour vous connecter manuellement:"
echo "  ./zappy_gui -p $PORT -h localhost"
echo "  ./zappy_ai -p $PORT -n <TEAM_NAME> -h localhost"
echo ""
echo "Appuyez sur Ctrl+C pour arrêter tous les processus"
echo "=========================================="

# Attendre indéfiniment (les processus continuent en arrière-plan)
while true; do
    # Vérifier si le serveur est toujours en vie
    if ! kill -0 $SERVER_PID 2>/dev/null; then
        log_error "Le serveur s'est arrêté !"
        cleanup
    fi

    sleep 5
done