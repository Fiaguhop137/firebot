#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <random>
using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::unordered_map;
std::random_device rd;
std::mt19937 gen(rd());
const vector<string> BASIC_POWERS={"fire","metal","wood","earth","water"};
const vector<string> ALIGNMENTS={"light","dark"};
const vector<string> COSMIC_POWERS={"space","time"};
const unordered_map<string,string>POWER_DEFINITIONS={
    {"fire","the power of flames and heat. You are able to control and manipulate flames, creating powerful attacks and defenses. You are also immune to fire and heat, allowing you to withstand extreme temperatures. You deal more damage to metal by melting it, but less to earth because it is not flammable. You have more defense towards wood since you can't put out fire by adding fuel, but less protection from water because water can extinguish fire."},
    {"metal","the power of strength and durability. You are able to control and manipulate metallic substanced, creating powerful weapons and armor. You are also immune to metal-based attacks such as bullets and blades, allowing you to withstand physical damage. You deal more damage to wood by cutting it, but less to water because water can cause rust. You have more defense towards earth since you are heavier than it, but less protection from fire because fire can melt metal."},
    {"wood","the power of growth and nature. You are able to control and manipulate plant life, creating powerful tools and structures. You are also immune to wood-based attacks, allowing you to withstand natural disasters. You deal more damage to earth since tree roots break up, penetrate, and bind soil together, but less to fire since you can't put out fire by adding fuel. You have more defense towards water because you drink water, but less protection from metal because metal can cut wood."},
    {"earth","the power of stability and protection. You are able to control and manipulate dirt, stone, and other earth materials, creating powerful barriers and fortifications. You are also immune to earth-based attacks, allowing you to withstand seismic activity. You deal more damage to water by soaking it up, but less to metal because metal is too durable. You have more defense towards fire you are non flammable, but less protection from wood because tree roots break up, penetrate, and bind soil together."},
    {"water","the power of fluidity and adaptability. You are able to control and manipulate water and ice, creating powerful waves and currents. You are also immune to water-based attacks, allowing you to withstand flooding. You deal more damage to fire by extinguishing it, but less to wood because wood can absorb water. You have more defense towards metal because it sinks in you, but less protection from earth because earth can absorb the water."},
    {"light","the power of illumination and vision. You are able to control and manipulate radiant energy, creating powerful beams and illusions. You are also immune to light-based attacks, allowing you to withstand bright environments. You deal more damage to dark by dispelling it, but take more damage from it as well since it obscures your vision."},
    {"dark","the power of negation and mystery. You are able to control and manipulate the absence of light and the shadows themself, creating powerful voids and illusions. You are also immune to dark-based attacks, allowing you to withstand eerie environments. You deal more damage to light by absorbing it, but take more damage to it as well because it blots out your shadows."},
    {"space","the power of dimensions and travel. You are able to control and manipulate the fabric of space, creating powerful portals and levitations. You are also immune to space-based attacks, allowing you to withstand vacuum and teleportation. You deal more damage to time by disrupting it, but take more damage from it as well since it is not in the 3 dimensions you exist in."},
    {"time","the power of past, present, and future. You are able to control and manipulate the flow of time, creating powerful time loops and see the future. You are also immune to time-based attacks, allowing you to withstand temporal anomalies. You deal more damage to space by disrupting it, but take more damage from it as well since it is not in your domain."}
};
struct Move {
    string name;
    int damage;
    int cooldown;
    string type;
    string level;
};
const unordered_map<string,Move>MOVES={
    {"flame_burst",{"Flame Burst",10,1,"fire","basic"}},
    {"fireball",{"Fireball",13,2,"fire","basic"}},
    {"heat_wave",{"Heat Wave",17,2,"fire","basic"}},
    {"iron_spike",{"Iron Spike",10,1,"metal","basic"}},
    {"shard_spray",{"Shard Spray",15,4,"metal","basic"}},
    {"knife_storm",{"Knife Storm",15,4,"metal","basic"}},
    {"splinter",{"Splinter",10,1,"wood","basic"}},
    {"vine_whip",{"Vine Whip",12,2,"wood","basic"}},
    {"leaf_storm",{"Leaf Storm",15,3,"wood","basic"}},
    {"pebble_shot",{"Pebble Shot",10,1,"earth","basic"}},
    {"tremor",{"Tremor",15,2,"earth","basic"}},
    {"boulder_crush",{"Boulder Crush",20,5,"earth","basic"}},
    {"water_jet",{"Water Jet",10,1,"water","basic"}},
    {"tidal_wave",{"Tidal Wave",15,2,"water","basic"}},
    {"flood",{"Flood",20,5,"water","basic"}},
    {"light_beam",{"Light Beam",10,1,"light","alignment"}},
    {"solar_flare",{"Solar Flare",15,4,"light","alignment"}},
    {"radiant_burst",{"Radiant Burst",12,3,"light","alignment"}},
    {"photon_bolt",{"Photon Bolt",20,5,"light","alignment"}},
    {"void_strike",{"Void Strike",10,1,"dark","alignment"}},
    {"shadow_flux",{"Shadow Flux",12,3,"dark","alignment"}},
    {"nightmare",{"Nightmare",15,4,"dark","alignment"}},
    {"eclipse",{"Eclipse",20,6,"dark","alignment"}},
    {"space_rift",{"Space Rift",10,1,"space","cosmic"}},
    {"gravity_well",{"Gravity Well",15,4,"space","cosmic"}},
    {"space_wormhole",{"Spatial Wormhole",20,5,"space","cosmic"}},
    {"singularity",{"Singularity",25,6,"space","cosmic"}},
    {"galactic_strike",{"Galactic Strike",17,3,"space","cosmic"}},
    {"chronic_chakram",{"Chronic Chakram",10,1,"time","cosmic"}},
    {"temporal_loop",{"Temporal Loop",19,3,"time","cosmic"}},
    {"time_wormhole",{"Temporal Wormhole",20,5,"time","cosmic"}},
    {"fortune",{"Fortune",13,3,"time","cosmic"}},
    {"destiny",{"Destiny",16,3,"time","cosmic"}}
};
string user_input(string prompt,vector<string>valid_options={}) {
    while(true){
        string response;
        cout<<prompt<<" ";
        if(!valid_options.empty()){
            cout<<"(";
            for(size_t i=0;i<valid_options.size()-1;i++) {
                cout<<valid_options[i];
                if(i<valid_options.size()-2) {
                    cout<<", ";
                }
            }
            cout<<" or "<<valid_options.back()<<") ";
        }
        cin>>response;
        if(!valid_options.empty()&&find(valid_options.begin(),valid_options.end(),response)==valid_options.end()){
            cout<<"Invalid input. Please choose ";
            for(size_t i=0;i<valid_options.size()-1;i++) {
                cout<<valid_options[i];
                if(i<valid_options.size()-2) {
                    cout<<", ";
                }
            }
            cout<<" or "<<valid_options.back()<<". ";
        }else{
            return(response);
        }
    }
}
struct Stats {
    int attack;
    int speed;
    int defense;
    int health;
};
struct Powers {
    string basic;
    string alignment;
    string cosmic;
};
struct Player {
    string name;
    int rare_traits=0;
    unordered_map<string,int>cooldown_times={};
    vector<string> known_moves;
    vector<string> pets;
    Stats stats{10,20,10,100};
    Powers powers;
    Player() {
        name=user_input("What would you like to name your character?");
        bool randomize=user_input("Would you like to randomize your character's stats and powers?",{"yes","no"})=="yes";
        if (randomize) {
            vector<string> basic_options={"fire","metal","wood","earth","water","fire","metal","wood","earth","water","nexus"};
            std::uniform_int_distribution<size_t> basic_dist(0,basic_options.size()-1);
            powers.basic=basic_options[basic_dist(gen)];
            vector<string> alignment_options={"light","light","light","light","dark","dark","dark","dark","objectivity"};
            std::uniform_int_distribution<size_t> alignment_dist(0,alignment_options.size()-1);
            powers.alignment=alignment_options[alignment_dist(gen)];
            vector<string> cosmic_options={"space","space","space","space","space","time","time","time","time","time","axiom"};
            std::uniform_int_distribution<size_t> cosmic_dist(0,cosmic_options.size()-1);
            powers.cosmic=cosmic_options[cosmic_dist(gen)];
        }else{
            powers.basic=user_input("What would you like your character's basic power to be?",BASIC_POWERS);
            powers.alignment=user_input("What would you like your character's alignment to be?",ALIGNMENTS);
            powers.cosmic=user_input("What would you like your character's cosmic power to be?",COSMIC_POWERS);
        }
        if (powers.basic=="fire"){known_moves.push_back("flame_burst");} 
        else if (powers.basic=="metal"){known_moves.push_back("iron_spike");} 
        else if (powers.basic=="wood"){known_moves.push_back("splinter");} 
        else if (powers.basic=="earth"){known_moves.push_back("pebble_shot");} 
        else if (powers.basic=="water"){known_moves.push_back("water_jet");} 
        else {vector<string> basic_moves={"flame_burst","iron_spike","splinter","pebble_shot","water_jet"};known_moves.insert(known_moves.end(),basic_moves.begin(),basic_moves.end());}
        if (powers.alignment=="light"){known_moves.push_back("light_beam");} 
        else if (powers.alignment=="dark"){known_moves.push_back("void_strike");} 
        else {vector<string> alignment_moves={"light_beam","void_strike"};known_moves.insert(known_moves.end(),alignment_moves.begin(),alignment_moves.end());}
        if (powers.cosmic=="space"){known_moves.push_back("space_rift");} 
        else if (powers.cosmic=="time"){known_moves.push_back("chronic_chakram");} 
        else {vector<string> cosmic_moves={"space_rift","chronic_chakram"};known_moves.insert(known_moves.end(),cosmic_moves.begin(),cosmic_moves.end());}
        if (powers.basic=="nexus"){rare_traits++;}
        if (powers.alignment=="objectivity"){rare_traits++;}
        if (powers.cosmic=="axiom"){rare_traits++;}
    }
};
int main() {
    Player player;
    return 0;
}