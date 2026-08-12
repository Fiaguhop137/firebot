#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <random>
#include <iterator>
using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::unordered_map;
const string BASIC_POWERS[5]={"fire","metal","wood","earth","water"};
const string ALIGNMENTS[2]={"light","dark"};
const string COSMIC_POWERS[2]={"space","time"};
unordered_map<string,string>POWER_DEFINITIONS={
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
unordered_map<string,Move>MOVES={
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
        cout<<prompt;
        if(!valid_options.empty()){
            cout<<" (";
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
    string name=user_input("What would you like to name your character?");
    bool rand=user_input("Would you like to randomize your character's stats and powers?",{"yes","no"})=="yes";
    if (rand) {
        std::uniform_int_distribution<int> dist(0,std::size(BASIC_POWERS)-1);
        string basic=BASIC_POWERS[dist(gen)];
        std::uniform_int_distribution<int> dist(0,std::size(ALIGNMENTS)-1);
        string basic=ALIGNMENTS[dist(gen)];
        std::uniform_int_distribution<int> dist(0,std::size(COSMIC_POWERS)-1);
        string basic=COSMIC_POWERS[dist(gen)];
    }
        basic=random.choice(BASIC_POWERS*2+["nexus"])
        alignment=random.choice(ALIGNMENTS*4+["objectivity"])
        cosmic=random.choice(COSMIC_POWERS*5+["axiom"])
    else:
        basic=user_input("What would you like your character's basic power to be?",BASIC_POWERS).lower()
        alignment=user_input("What would you like your character's alignment to be?",ALIGNMENTS).lower()
        cosmic=user_input("What would you like your character's cosmic power to be?",COSMIC_POWERS).lower()
    self.stats=stats(10,20,10,100)
    self.powers=powers(basic,alignment,cosmic)
    self.known_moves=["flame_burst"if basic=="fire"else"iron_spike"if basic=="metal"else"splinter"if basic=="wood"else"pebble_shot"if basic=="earth"else"water_jet"]
    self.cooldown_times={}
    self.pets=[]
    self.rare_traits=((self.powers.basic=="nexus")+(self.powers.alignment=="objectivity")+(self.powers.cosmic=="axiom"))
}
int main() {
    string power=user_input("What is your power?",{"fire","metal","wood","earth","water"});
    cout<<power<<"\n";
    return 0;
}