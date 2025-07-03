/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The Commands class declaration
*/
/**
 * @file Commands.hpp
 * @brief The Commands class declaration
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#ifndef COMMANDS_HPP
    #define COMMANDS_HPP

    #include "Graphics.hpp"
    #include "QueueManager.hpp"

namespace Gui
{
    //////////////////// Custom Constants //////////////////////////////////

    static constexpr const char *MSZ = "msz"; // Map size
    static constexpr const char *BCT = "bct"; // Content
    static constexpr const char *TNA = "tna"; // Name of all the teams
    static constexpr const char *PNW = "pnw"; // Connection of a new player
    static constexpr const char *PPO = "ppo"; // Player's position
    static constexpr const char *PLV = "plv"; // Player's level
    static constexpr const char *PIN = "pin"; // Player inventory
    static constexpr const char *PEX = "pex"; // Expulsion
    static constexpr const char *PBC = "pbc"; // Broadcast
    static constexpr const char *PIC = "pic"; // Start of an incantation (by the first player)
    static constexpr const char *PIE = "pie"; // End of an incantation
    static constexpr const char *PFK = "pfk"; // Egg laying by the player
    static constexpr const char *PDR = "pdr"; // Resource dropping
    static constexpr const char *PGT = "pgt"; // Resource collecting
    static constexpr const char *PDI = "pdi"; // Death of a player
    static constexpr const char *ENW = "enw"; // An egg was laid by a player
    static constexpr const char *EBO = "ebo"; // Player connection for an egg
    static constexpr const char *EDI = "edi"; // Death of an egg
    static constexpr const char *SGT = "sgt"; // Time unit request
    static constexpr const char *SST = "sst"; // Time unit modification
    static constexpr const char *SEG = "seg"; // End of game
    static constexpr const char *SMG = "smg"; // Message from the server
    static constexpr const char *SUC = "suc"; // Unknown command
    static constexpr const char *SBP = "sbp"; // Command parameter



    /**
     * @class Commands
     * @brief The Commands class handles the commands received from the server.
     */
    class Commands {
        public:

            //////////////////// Constructors and Destructor ///////////////////////

            /**
             * @brief Construct a new Commands object.
             */
            Commands(Graphics &graphical);

            /**
             * @brief Destroy the Commands object.
             */
            ~Commands() = default;



            //////////////////// Main Methods //////////////////////////////////////

            /**
             * @brief Handle a command.
             */
            void handleResponses(std::shared_ptr<QueueManager> &);

            /**
             * @brief Handle the MSZ command.
             */
            void handleMSZ(std::string &param);

            /**
             * @brief Handle the BCT command.
             */
            void handleBCT(std::string &param);

            /**
             * @brief Handle the TNA command.
             */
            void handleTNA(std::string &param);

            /**
             * @brief Handle the PNW command.
             */
            void handlePNW(std::string &param);

            /**
             * @brief Handle the PPO command.
             */
            void handlePPO(std::string &param);

            /**
             * @brief Handle the PLV command.
             */
            void handlePLV(std::string &param);

            /**
             * @brief Handle the PIN command.
             */
            void handlePIN(std::string &param);

            /**
             * @brief Handle the PEX command.
             */
            void handlePEX(std::string &param);

            /**
             * @brief Handle the PBC command.
             */
            void handlePBC(std::string &param);

            /**
             * @brief Handle the PIC command.
             */
            void handlePIC(std::string &param);

            /**
             * @brief Handle the PIE command.
             */
            void handlePIE(std::string &param);

            /**
             * @brief Handle the PFK command.
             */
            void handlePFK(std::string &param);

            /**
             * @brief Handle the PDR command.
             */
            void handlePDR(std::string &param);

            /**
             * @brief Handle the PGT command.
             */
            void handlePGT(std::string &param);

            /**
             * @brief Handle the PDI command.
             */
            void handlePDI(std::string &param);

            /**
             * @brief Handle the ENW command.
             */
            void handleENW(std::string &param);

            /**
             * @brief Handle the EBO command.
             */
            void handleEBO(std::string &param);

            /**
             * @brief Handle the EDI command.
             */
            void handleEDI(std::string &param);

            /**
             * @brief Handle the SGT command.
             */
            void handleSGT(std::string &param);

            /**
             * @brief Handle the SST command.
             */
            void handleSST(std::string &param);

            /**
             * @brief Handle the SEG command.
             */
            void handleSEG(std::string &param);

            /**
             * @brief Handle the SMG command.
             */
            void handleSMG(std::string &param);

            /**
             * @brief Handle the SUC command.
             */
            void handleSUC(std::string &param);

            /**
             * @brief Handle the SBP command.
             */
            void handleSBP(std::string &param);



        private:

            //////////////// Private Attributes ////////////////////////////////

            std::unordered_map<std::string, std::function<void(std::string &)>> _commandHandlers; ///< Map of command handlers
            Graphics &_graphical; ///< Reference to the graphical object for drawing
    };
}

#endif /* !COMMANDS_HPP */
