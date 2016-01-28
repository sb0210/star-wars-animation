
#include <fstream>
#include <stdlib.h>  
#include <unistd.h>

extern float light1,light2,light3; 
extern int enable_animation;

extern int fps ;
extern std::ofstream outfile;
extern std::ifstream infile;

extern GLfloat c_xpos , c_ypos , c_zpos ;
extern GLfloat c_up_x , c_up_y , c_up_z ;
extern GLfloat c_xrot,c_yrot,c_zrot;
extern GLfloat c_tx, c_ty, c_tz;



void camera_frames(std::ofstream & outfile){
    outfile<<"Camera_Pos "<<c_xpos<<" "<<c_ypos<<" "<<c_zpos<<std::endl;
    outfile<<"Up_Vector_Pos "<<c_up_x<<" "<<c_up_y<<" "<<c_up_z<<std::endl;
    outfile<<"Target_Pos "<<c_tx<<" "<<c_ty<<" "<<c_tz<<std::endl;
}

void lights_frames(std::ofstream & outfile){
    outfile<<"Lights "<<light1<<" "<<light2<<" "<<light3<<std::endl;
}

void camera_frames(std::ifstream & infile){
    std::string s;
    infile>>s>>c_xpos>>c_ypos>>c_zpos;
    infile>>s>>c_up_x>>c_up_y>>c_up_z;
    infile>>s>>c_tx>>c_ty>>c_tz;
}

void lights_frames(std::ifstream & infile){
    std::string s;
    infile>>s>>light1>>light2>>light3;
}

void store_key_frames(){
    std::cout<<"Stored_key_frame"<<std::endl;
    starwars->store_key_frames(outfile);
    camera_frames(outfile);
    lights_frames(outfile);
    outfile<<"Stored_key_frame"<<std::endl;
}

void create_key_frames(){

    float a[145];
    float b[145];
    std::ifstream inp;
    inp.open("keyframes.txt",std::ios_base::in);
    std::ofstream final_output;
    final_output.open("final_output.txt",std::ios_base::out);
    std::string s;
    int n_frames=30;
    for(int i=0;i<145;i++){
        if(i<133){
            inp>>a[i];
        }
        else{
            if((i-133)%3==0){
                inp>>s;
            }
            inp>>a[i];
        }
    }
    inp>>s;
    while(!inp.eof()){
        for(int i=0;i<145;i++){
            if(i<133){
                inp>>b[i];
            }
            else{
                if((i-133)%3==0){
                    inp>>s;
                }
                inp>>b[i];
            }
        }    
        inp>>s;
        for(int k=0;k<n_frames;k++){
            for(int i=0;i<145;i=i){
                if(i<133){
                    float temp[7];
                    temp[0]=a[i]+((b[i]-a[i])*k)/n_frames;
                    i++;
                    temp[1]=a[i]+((b[i]-a[i])*k)/n_frames;
                    i++;
                    temp[2]=a[i]+((b[i]-a[i])*k)/n_frames;
                    i++;
                    temp[3]=a[i]+((b[i]-a[i])*k)/n_frames;
                    i++;
                    temp[4]=a[i]+((b[i]-a[i])*k)/n_frames;
                    i++;
                    temp[5]=a[i]+((b[i]-a[i])*k)/n_frames;
                    i++;
                    temp[6]=a[i];
                    i++;
                    final_output<<temp[0]<<" "<<temp[1]<<" "<<temp[2]<<" "<<temp[3]<<" "<<temp[4]<<" "<<temp[5]<<" "<<temp[6]<<std::endl;
                }
                else{
                    if(i==133){
                        s="Camera_Pos";
                    }
                    else if(i==136){
                        s="Up_Vector_Pos";
                    }
                    else if(i==139){
                        s="Target_Pos";
                    }
                    else if(i==142){
                        s="Lights";
                    }
                    float temp[3];
                    
                    if(i==142){
                        temp[0]=a[i];i++;
                        temp[1]=a[i];i++;
                        temp[2]=a[i];i++;
                    }
                    else{
                        temp[0]=a[i]+((b[i]-a[i])*k)/n_frames;
                        i++;
                        temp[1]=a[i]+((b[i]-a[i])*k)/n_frames;
                        i++;
                        temp[2]=a[i]+((b[i]-a[i])*k)/n_frames;
                        i++;
                    }
                    final_output<<s<<" "<<temp[0]<<" "<<temp[1]<<" "<<temp[2]<<std::endl;                    
                }
            }
            final_output<<"Stored_key_frame"<<std::endl;
        }
        for(int i=0;i<145;i++){
            a[i]=b[i];
        }
    }
}


void load_key_frames(){
    if(!infile.eof()){
        starwars->load_key_frames(infile);
        camera_frames(infile);
        lights_frames(infile);
        std::string s;
        infile>>s;
    }
    else{
        std::cout<<"playback_stopped"<<std::endl;
        enable_animation=0;
        infile.close();
    }
}

void call_back(){
    int sleep_time = 1000000/fps;
    load_key_frames();
    usleep(sleep_time);
}
void reset_files(){
    std::cout<<"reset_files"<<std::endl;
    outfile.close();
    outfile.open("keyframes.txt", std::ios_base::out);
    outfile<<" ";
}

void start_playback(){
    std::cout<<"start_playback"<<std::endl;
    create_key_frames();
    infile.open ("final_output.txt", std::ifstream::in);
    enable_animation=1;    
}
