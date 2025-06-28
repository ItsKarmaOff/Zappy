import React, { useState, useEffect } from 'react';
import { ChevronDown, Users, Network, Eye, Bot, Server, Monitor, Star, Github, Play, X, Menu } from 'lucide-react';

const ZappyWebsite = () => {
    const [activeSection, setActiveSection] = useState('home');
    const [animateTitle, setAnimateTitle] = useState(false);
    const [showVideoModal, setShowVideoModal] = useState(false);
    const [isMobileMenuOpen, setIsMobileMenuOpen] = useState(false);

    useEffect(() => {
        setAnimateTitle(true);

        const handleEscape = (e) => {
            if (e.key === 'Escape') {
                setShowVideoModal(false);
                setIsMobileMenuOpen(false);
            }
        };

        if (showVideoModal) {
            document.addEventListener('keydown', handleEscape);
            document.body.style.overflow = 'hidden';
        }

        if (isMobileMenuOpen) {
            document.addEventListener('keydown', handleEscape);
            document.body.style.overflow = 'hidden';
        }

        return () => {
            document.removeEventListener('keydown', handleEscape);
            document.body.style.overflow = 'unset';
        };
    }, [showVideoModal, isMobileMenuOpen]);

    const openGitHub = () => {
        const githubUrl = process.env.REACT_APP_GITHUB_URL;

        if (githubUrl) {
            window.open(githubUrl, '_blank');
        } else {
            console.error('GitHub URL not configured');
        }
    };

    const openDemo = () => {
        setShowVideoModal(true);
    };

    const closeModal = () => {
        setShowVideoModal(false);
    };

    const handleMobileNavigation = (section) => {
        setActiveSection(section);
        setIsMobileMenuOpen(false);
    };

    const teamMembers = [
        { name: "Christophe Vandevoir", role: "GUI Developer & Graphics", photo: "/Zappy/assets/photos/christophe_vandevoir.png", github: "ItsKarmaOff" },
        { name: "Gianni Tuero", role: "GUI Developer & Graphics", photo: "/Zappy/assets/photos/gianni_tuero.png", github: "xJundo" },
        { name: "Lou Pellegrino", role: "Server Architecture", photo: "/Zappy/assets/photos/lou_pellegrino.png", github: "DimitriLaPoudre" },
        { name: "Nicolas Toro", role: "Server Architecture", photo: "/Zappy/assets/photos/nicolas_toro.png", github: "toro-nicolas" },
        { name: "Olivier Pouech", role: "AI Developer & Algorithms", photo: "/Zappy/assets/photos/olivier_pouech.png", github: "Livoooo" },
        { name: "Raphaël Launay", role: "AI Developer & Algorithms", photo: "/Zappy/assets/photos/raphael_launay.png", github: "frenchkiwi" }
    ];

    const resources = [
        { name: "Food", image: "/Zappy/assets/ressources/food.png", density: "0.5" },
        { name: "Linemate", image: "/Zappy/assets/ressources/linemate.png", density: "0.3" },
        { name: "Deraumere", image: "/Zappy/assets/ressources/deraumere.png", density: "0.15" },
        { name: "Sibur", image: "/Zappy/assets/ressources/sibur.png", density: "0.1" },
        { name: "Mendiane", image: "/Zappy/assets/ressources/mendiane.png", density: "0.1" },
        { name: "Phiras", image: "/Zappy/assets/ressources/phiras.png", density: "0.08" },
        { name: "Thystame", image: "/Zappy/assets/ressources/thystame.png", density: "0.05" }
    ];

    const elevationLevels = [
        { level: "1 → 2", players: 1, resources: "1 Linemate" },
        { level: "2 → 3", players: 2, resources: "1 Linemate, 1 Deraumere, 1 Sibur" },
        { level: "3 → 4", players: 2, resources: "2 Linemate, 1 Sibur, 2 Phiras" },
        { level: "4 → 5", players: 4, resources: "1 Linemate, 1 Deraumere, 2 Sibur, 1 Phiras" },
        { level: "5 → 6", players: 4, resources: "1 Linemate, 2 Deraumere, 1 Sibur, 3 Mendiane" },
        { level: "6 → 7", players: 6, resources: "1 Linemate, 2 Deraumere, 3 Sibur, 1 Phiras" },
        { level: "7 → 8", players: 6, resources: "2 Linemate, 2 Deraumere, 2 Sibur, 2 Mendiane, 2 Phiras, 1 Thystame" }
    ];

    return (
        <div className="min-h-screen bg-gradient-to-br from-slate-900 via-purple-900 to-slate-900 text-white overflow-x-hidden">
            {/* Navigation */}
            <nav className="fixed top-0 w-full z-50 bg-black/20 backdrop-blur-md border-b border-purple-500/30">
                <div className="container mx-auto px-6 py-4">
                    <div className="flex justify-between items-center">
                        <div className="text-2xl font-bold bg-gradient-to-r from-purple-400 to-cyan-400 bg-clip-text text-transparent">
                            ZAPPY
                        </div>

                        {/* Desktop Navigation */}
                        <div className="hidden md:flex space-x-6">
                            {['home', 'about', 'team', 'tech'].map((section) => (
                                <button
                                    key={section}
                                    onClick={() => setActiveSection(section)}
                                    className={`capitalize transition-all duration-300 hover:text-purple-400 ${activeSection === section ? 'text-purple-400 border-b-2 border-purple-400' : ''
                                        }`}
                                >
                                    {section === 'tech' ? 'Technologies' : section}
                                </button>
                            ))}
                        </div>

                        {/* Hamburger Mobile Button */}
                        <button
                            onClick={() => setIsMobileMenuOpen(!isMobileMenuOpen)}
                            className="md:hidden p-2 rounded-lg hover:bg-purple-500/20 transition-colors duration-300"
                        >
                            {isMobileMenuOpen ? (
                                <X size={24} className="text-purple-400" />
                            ) : (
                                <Menu size={24} className="text-purple-400" />
                            )}
                        </button>
                    </div>
                </div>

                {/* Mobile Menu */}
                <div className={`md:hidden absolute top-full left-0 w-full bg-black/95 backdrop-blur-md border-b border-purple-500/30 transition-all duration-300 ${isMobileMenuOpen
                    ? 'opacity-100 visible transform translate-y-0'
                    : 'opacity-0 invisible transform -translate-y-4'
                    }`}>
                    <div className="container mx-auto px-6 py-4">
                        <div className="flex flex-col space-y-4">
                            {['home', 'about', 'team', 'tech'].map((section) => (
                                <button
                                    key={section}
                                    onClick={() => handleMobileNavigation(section)}
                                    className={`capitalize text-left py-3 px-4 rounded-lg transition-all duration-300 hover:bg-purple-500/20 ${activeSection === section
                                        ? 'text-purple-400 bg-purple-500/10 border-l-4 border-purple-400'
                                        : 'text-white hover:text-purple-400'
                                        }`}
                                >
                                    {section === 'tech' ? 'Technologies' : section}
                                </button>
                            ))}
                        </div>
                    </div>
                </div>
            </nav>

            {/* Overlay to close mobile menu */}
            {isMobileMenuOpen && (
                <div
                    className="fixed inset-0 bg-black/50 z-40 md:hidden"
                    onClick={() => setIsMobileMenuOpen(false)}
                />
            )}

            {/* Hero Section */}
            {activeSection === 'home' && (
                <section className="min-h-screen flex items-center justify-center relative overflow-hidden">
                    {/* Animated Background */}
                    <div className="absolute inset-0">
                        {[...Array(50)].map((_, i) => (
                            <div
                                key={i}
                                className="absolute w-1 h-1 bg-purple-400 rounded-full animate-pulse"
                                style={{
                                    left: `${Math.random() * 100}%`,
                                    top: `${Math.random() * 100}%`,
                                    animationDelay: `${Math.random() * 3}s`,
                                    animationDuration: `${2 + Math.random() * 3}s`
                                }}
                            />
                        ))}
                    </div>

                    <div className="text-center z-10 px-6">
                        <h1 className={`text-4xl sm:text-6xl md:text-8xl font-bold mb-6 transition-all duration-1000 ${animateTitle ? 'translate-y-0 opacity-100' : 'translate-y-20 opacity-0'
                            }`}>
                            <span className="bg-gradient-to-r from-purple-400 via-pink-400 to-cyan-400 bg-clip-text text-transparent">
                                ZAPPY
                            </span>
                        </h1>
                        <p className="text-lg sm:text-xl md:text-2xl mb-8 text-gray-300 max-w-3xl mx-auto">
                            Network Multiplayer Game
                        </p>
                        <p className="text-base sm:text-lg mb-12 text-gray-400 max-w-4xl mx-auto">
                            Explore the world of Trantor, collect mystical resources and lead your team to the ultimate elevation in this C/C++ multiplayer game.
                        </p>

                        <div className="flex flex-col sm:flex-row justify-center gap-4">
                            <button
                                onClick={openDemo}
                                className="bg-gradient-to-r from-purple-600 to-pink-600 px-8 py-4 rounded-full text-lg font-semibold hover:scale-105 transition-transform duration-300 flex items-center justify-center gap-2"
                            >
                                <Play size={20} />
                                View Demo
                            </button>
                            <button
                                onClick={openGitHub}
                                className="border-2 border-purple-400 px-8 py-4 rounded-full text-lg font-semibold hover:bg-purple-400/10 transition-all duration-300 flex items-center justify-center gap-2"
                            >
                                <Github size={20} />
                                Source Code
                            </button>
                        </div>
                    </div>

                    <div className="absolute bottom-8 left-1/2 transform -translate-x-1/2 animate-bounce">
                        <ChevronDown size={32} className="text-purple-400" />
                    </div>
                </section>
            )}

            {/* About Section */}
            {activeSection === 'about' && (
                <section className="min-h-screen py-20 px-6">
                    <div className="container mx-auto max-w-6xl">
                        <h2 className="text-3xl sm:text-4xl md:text-5xl font-bold text-center mb-16 bg-gradient-to-r from-purple-400 to-cyan-400 bg-clip-text text-transparent">
                            About Zappy
                        </h2>

                        <div className="grid md:grid-cols-2 gap-12 mb-16">
                            <div className="bg-black/30 backdrop-blur-sm rounded-2xl p-8 border border-purple-500/30">
                                <h3 className="text-2xl font-bold mb-4 text-purple-400">The World of Trantor</h3>
                                <p className="text-gray-300 mb-4">
                                    Trantor is a terrain-free world where several teams compete to collect resources and reach the maximum elevation.
                                </p>
                                <p className="text-gray-300">
                                    The goal is to be the first team to have at least 6 players who reach the maximum elevation level.
                                </p>
                            </div>

                            <div className="bg-black/30 backdrop-blur-sm rounded-2xl p-8 border border-purple-500/30">
                                <h3 className="text-2xl font-bold mb-4 text-purple-400">Technical Architecture</h3>
                                <p className="text-gray-300 mb-4">
                                    The project consists of three main components: a C server, a C++ graphical interface, and stand-alone AI clients.
                                </p>
                                <p className="text-gray-300">
                                    Communication via TCP sockets with a custom protocol to synchronize the game state.
                                </p>
                            </div>
                        </div>

                        {/* Resources Grid */}
                        <div className="mb-16">
                            <h3 className="text-2xl sm:text-3xl font-bold text-center mb-8 text-purple-400">Trantor Resources</h3>
                            <div className="grid grid-cols-2 sm:grid-cols-3 md:grid-cols-4 lg:grid-cols-7 gap-4">
                                {resources.map((resource, index) => (
                                    <div key={index} className="bg-black/30 backdrop-blur-sm rounded-xl p-4 border border-purple-500/30 text-center hover:scale-105 transition-transform duration-300">
                                        <div className="w-12 h-12 mx-auto mb-3">
                                            <img
                                                src={resource.image}
                                                alt={resource.name}
                                                className="w-full h-full object-contain drop-shadow-lg"
                                                onError={(e) => {
                                                    e.target.src = `https://ui-avatars.com/api/?name=${encodeURIComponent(resource.name.charAt(0))}&background=8b5cf6&color=ffffff&size=48&bold=true`;
                                                }}
                                            />
                                        </div>
                                        <h4 className="font-bold text-sm mb-1">{resource.name}</h4>
                                        <p className="text-xs text-gray-400">Density: {resource.density}</p>
                                    </div>
                                ))}
                            </div>
                        </div>

                        {/* Elevation Levels */}
                        <div>
                            <h3 className="text-2xl sm:text-3xl font-bold text-center mb-8 text-purple-400">Elevation Rituals</h3>
                            <div className="space-y-4">
                                {elevationLevels.map((level, index) => (
                                    <div key={index} className="bg-black/30 backdrop-blur-sm rounded-xl p-6 border border-purple-500/30 hover:border-purple-400/50 transition-colors duration-300">
                                        <div className="flex flex-col md:flex-row md:items-center justify-between">
                                            <div className="flex items-center gap-4 mb-2 md:mb-0">
                                                <span className="bg-gradient-to-r from-purple-500 to-pink-500 px-3 py-1 rounded-full text-sm font-bold">
                                                    Level {level.level}
                                                </span>
                                                <span className="text-purple-400">
                                                    <Users size={16} className="inline mr-1" />
                                                    {level.players} player{level.players > 1 ? 's' : ''}
                                                </span>
                                            </div>
                                            <div className="text-gray-300 text-sm">
                                                {level.resources}
                                            </div>
                                        </div>
                                    </div>
                                ))}
                            </div>
                        </div>
                    </div>
                </section>
            )}

            {/* Team Section */}
            {activeSection === 'team' && (
                <section className="min-h-screen py-20 px-6">
                    <div className="container mx-auto max-w-6xl">
                        <h2 className="text-3xl sm:text-4xl md:text-5xl font-bold text-center mb-16 bg-gradient-to-r from-purple-400 to-cyan-400 bg-clip-text text-transparent">
                            Our Team
                        </h2>

                        <div className="grid sm:grid-cols-2 lg:grid-cols-3 gap-8">
                            {teamMembers.map((member, index) => (
                                <div key={index} className="bg-black/30 backdrop-blur-sm rounded-2xl p-8 border border-purple-500/30 hover:border-purple-400/50 transition-all duration-300 hover:scale-105 group">
                                    <div className="text-center">
                                        <div className="w-24 h-24 mx-auto mb-4 relative group-hover:scale-110 transition-transform duration-300">
                                            <img
                                                src={member.photo}
                                                alt={member.name}
                                                className="w-full h-full rounded-full object-cover border-4 border-purple-400/50 shadow-lg group-hover:border-purple-300 transition-colors duration-300"
                                                onError={(e) => {
                                                    e.target.src = `https://ui-avatars.com/api/?name=${encodeURIComponent(member.name)}&background=8b5cf6&color=ffffff&size=200&bold=true`;
                                                }}
                                            />
                                            {/* Effet de brillance */}
                                            <div className="absolute inset-0 rounded-full bg-gradient-to-tr from-transparent via-white/20 to-transparent opacity-0 group-hover:opacity-100 transition-opacity duration-300"></div>
                                        </div>
                                        <h3 className="text-xl font-bold mb-2 text-purple-400">{member.name}</h3>
                                        <p className="text-gray-300 mb-4">{member.role}</p>
                                        <button
                                            onClick={() => window.open(`https://github.com/${member.github}`, '_blank')}
                                            className="flex items-center gap-2 mx-auto text-purple-400 hover:text-purple-300 transition-colors duration-300"
                                        >
                                            <Github size={18} />
                                            @{member.github}
                                        </button>
                                    </div>
                                </div>
                            ))}
                        </div>

                        <div className="text-center mt-16">
                            <p className="text-gray-400 text-lg">
                                A passionate team of Epitech students dedicated to creating a unique gaming experience
                            </p>
                        </div>
                    </div>
                </section>
            )}

            {/* Tech Section */}
            {activeSection === 'tech' && (
                <section className="min-h-screen py-20 px-6">
                    <div className="container mx-auto max-w-6xl">
                        <h2 className="text-3xl sm:text-4xl md:text-5xl font-bold text-center mb-16 bg-gradient-to-r from-purple-400 to-cyan-400 bg-clip-text text-transparent">
                            Technologies & Architecture
                        </h2>

                        <div className="grid md:grid-cols-3 gap-8 mb-16">
                            <div className="bg-black/30 backdrop-blur-sm rounded-2xl p-8 border border-purple-500/30 text-center hover:scale-105 transition-transform duration-300">
                                <Server size={64} className="mx-auto mb-4 text-purple-400" />
                                <h3 className="text-2xl font-bold mb-4 text-purple-400">Server</h3>
                                <p className="text-gray-300 mb-4">Developed in C with TCP socket management and multiplexing via poll()</p>
                                <div className="flex flex-wrap justify-center gap-2">
                                    <span className="bg-purple-600/20 px-3 py-1 rounded-full text-sm">C</span>
                                    <span className="bg-purple-600/20 px-3 py-1 rounded-full text-sm">TCP Sockets</span>
                                    <span className="bg-purple-600/20 px-3 py-1 rounded-full text-sm">Poll</span>
                                </div>
                            </div>

                            <div className="bg-black/30 backdrop-blur-sm rounded-2xl p-8 border border-purple-500/30 text-center hover:scale-105 transition-transform duration-300">
                                <Monitor size={64} className="mx-auto mb-4 text-cyan-400" />
                                <h3 className="text-2xl font-bold mb-4 text-cyan-400">Graphical User Interface</h3>
                                <p className="text-gray-300 mb-4">Modern C++ GUI with real-time 3D visualization</p>
                                <div className="flex flex-wrap justify-center gap-2">
                                    <span className="bg-cyan-600/20 px-3 py-1 rounded-full text-sm">C++</span>
                                    <span className="bg-cyan-600/20 px-3 py-1 rounded-full text-sm">Raylib</span>
                                    <span className="bg-cyan-600/20 px-3 py-1 rounded-full text-sm">Graphics</span>
                                </div>
                            </div>

                            <div className="bg-black/30 backdrop-blur-sm rounded-2xl p-8 border border-purple-500/30 text-center hover:scale-105 transition-transform duration-300">
                                <Bot size={64} className="mx-auto mb-4 text-pink-400" />
                                <h3 className="text-2xl font-bold mb-4 text-pink-400">Artificial Intelligence</h3>
                                <p className="text-gray-300 mb-4">Intelligent AI customers with adaptive strategies</p>
                                <div className="flex flex-wrap justify-center gap-2">
                                    <span className="bg-pink-600/20 px-3 py-1 rounded-full text-sm">C++</span>
                                    <span className="bg-pink-600/20 px-3 py-1 rounded-full text-sm">Algorithms</span>
                                    <span className="bg-pink-600/20 px-3 py-1 rounded-full text-sm">Strategy</span>
                                </div>
                            </div>
                        </div>

                        <div className="grid md:grid-cols-2 gap-8">
                            <div className="bg-black/30 backdrop-blur-sm rounded-2xl p-8 border border-purple-500/30">
                                <h3 className="text-2xl font-bold mb-4 text-purple-400 flex items-center gap-2">
                                    <Network size={24} />
                                    Communication Protocol
                                </h3>
                                <ul className="space-y-2 text-gray-300">
                                    <li>• Client/server TCP communication</li>
                                    <li>• Optimized binary protocol</li>
                                    <li>• Real-time management of events</li>
                                    <li>• Multi-client synchronization</li>
                                    <li>• Buffer of orders up to 10 requests</li>
                                </ul>
                            </div>

                            <div className="bg-black/30 backdrop-blur-sm rounded-2xl p-8 border border-purple-500/30">
                                <h3 className="text-2xl font-bold mb-4 text-purple-400 flex items-center gap-2">
                                    <Eye size={24} />
                                    Advanced Features
                                </h3>
                                <ul className="space-y-2 text-gray-300">
                                    <li>• Limited vision scalable by level</li>
                                    <li>• Directional broadcast system</li>
                                    <li>• Spherical world (wraparound)</li>
                                    <li>• Management of elevation rituals</li>
                                    <li>• Breeding and hatching of eggs</li>
                                </ul>
                            </div>
                        </div>
                    </div>
                </section>
            )}

            {/* Video Modal */}
            {showVideoModal && (
                <div
                    className="fixed inset-0 z-50 flex items-center justify-center bg-black/80 backdrop-blur-sm"
                    onClick={closeModal}
                >
                    <div
                        className="relative w-full max-w-4xl mx-4"
                        onClick={(e) => e.stopPropagation()}
                    >
                        {/* Close button */}
                        <button
                            onClick={closeModal}
                            className="absolute -top-12 right-0 text-white hover:text-purple-400 transition-colors duration-300"
                        >
                            <X size={32} />
                        </button>

                        {/* Video container */}
                        <div className="bg-black rounded-2xl overflow-hidden border border-purple-500/30">
                            <div className="aspect-video">
                                <iframe
                                    width="100%"
                                    height="100%"
                                    src="https://www.youtube.com/embed/hvL1339luv0?autoplay=1"
                                    title="Zappy Demo"
                                    frameBorder="0"
                                    allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture"
                                    allowFullScreen
                                    className="w-full h-full"
                                ></iframe>
                            </div>

                            {/* Video info */}
                            <div className="p-6">
                                <h3 className="text-xl font-bold text-purple-400 mb-2">
                                    🎮 Zappy demonstration
                                </h3>
                                <p className="text-gray-300">
                                    Discover our game in action: C server, C++ graphical interface, and autonomous AI compete on Trantor!
                                </p>
                            </div>
                        </div>
                    </div>
                </div>
            )}

            {/* Footer */}
            <footer className="bg-black/50 backdrop-blur-sm py-8 px-6 border-t border-purple-500/30">
                <div className="container mx-auto max-w-6xl text-center">
                    <div className="flex justify-center items-center gap-4 mb-4">
                        <span className="text-2xl font-bold bg-gradient-to-r from-purple-400 to-cyan-400 bg-clip-text text-transparent">
                            ZAPPY
                        </span>
                        <Star className="text-purple-400" size={20} />
                        <span className="text-gray-400">Epitech 2025 project</span>
                    </div>
                    <p className="text-gray-500">
                        Developed by a team of 6 Epitech students
                    </p>
                </div>
            </footer>
        </div>
    );
};

export default ZappyWebsite;