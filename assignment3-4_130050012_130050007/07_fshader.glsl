#version 330

in vec3 normal;
in vec4 eye;
in vec4 COLOR;
in vec2 tex;
in vec4 spotlight_point_Dir;

uniform mat4 viewMatrix;
uniform sampler2D texture;
uniform float b;
uniform float light1;
uniform float light2;
uniform float light3;

uniform float enable_texture;

uniform vec4 diffuse;
uniform vec4 ambient;
uniform vec4 specular;
uniform float shininess;
uniform float is_cone;

out vec4 frag_color;

void main () 
{	
 

	vec4 tempcolor= COLOR;

	if(b<0){

		  vec4 final_light1=vec4(0.0);
		  vec4 final_light2=vec4(0.0);
		  vec4 final_light3=vec4(0.0);
		  vec4 final_light4=vec4(0.0);
		  vec3 n = normalize(vec3(normal));	    


		  //Spotlight
		if(light3>0){
			float coneAngle = 1;    
   			vec3 coneDirection = vec3(0,-1,0); 
   			// vec4 coneDirection_ccs = viewMatrix * coneDirection;
   			// vec3 coneDirection1 = normalize(vec3(coneDirection_ccs));
		  vec4 spotlightPos = vec4(0.0, 30.0, 0.0, 1.0);
		  vec4 spotlightPos_ccs = viewMatrix * spotlightPos;
		  vec3 lightDir1 = normalize(vec3(spotlight_point_Dir)) ;
		  vec3 lightDir_ccs = normalize(vec3( viewMatrix * spotlight_point_Dir));
		 

		  //Diffuse
		  float cone_dotproduct = dot(coneDirection, -1 * lightDir1);
		  float dotProduct1 = dot(n, lightDir_ccs);
		  float intensity1 = 0;  
		  vec4 spec1 = vec4(0.0); 
			if(cone_dotproduct > 0.9 ){
			  intensity1=max( dotProduct1, 0.0);

			  if(intensity1 > 0.0)
			  {
				vec3 e = normalize(vec3(eye));
				vec3 h = normalize(lightDir_ccs + e );
			   	float intSpec = max(dot(h,n), 0.0);	
			        spec1 = specular * pow(intSpec, shininess);
			  }
			}

			final_light3= (intensity1* diffuse +spec1) ;   
		 
		} 

		  // Defining Light 1
		if(light1>0){
		  vec4 lightPos1 = vec4(1.0, 1.0, 1.0, 0.0);
		  vec3 lightDir1 = vec3(viewMatrix * lightPos1);  // Transforms with camera
		  lightDir1 = normalize( vec3(lightDir1));  

		  //Diffuse
		  


			 float dotProduct1 = dot(n, lightDir1);
		  float intensity1 =  max( dotProduct1, 0.0);
		  vec4 spec1 = vec4(0.0); 

		  if(intensity1 > 0.0)
		  {
			vec3 e = normalize(vec3(eye));
			vec3 h = normalize(lightDir1 + e );
		   	float intSpec = max(dot(h,n), 0.0);	
		        spec1 = specular * pow(intSpec, shininess);
		  }

		  final_light1= (intensity1* diffuse +spec1) ;   
		}

		if(light2 > 0){

		  vec4 lightPos2 = vec4(-1.0, 1.0, 1.0, 0.0);
		  vec3 lightDir2 = vec3(viewMatrix * lightPos2);  // Transforms with camera
		  lightDir2 = normalize( vec3(lightDir2));  

		  //Diffuse
		  float dotProduct2 = dot(n, lightDir2);
		  float intensity2 =  max( dotProduct2, 0.0);
		  vec4 spec2 = vec4(0.0); 

		  // Compute specular component only if light falls on vertex
		  

		  if(intensity2 > 0.0)
		  {
		  	vec3 n = normalize(vec3(normal));	 
			vec3 e = normalize(vec3(eye));
			vec3 h = normalize(lightDir2 + e );
		   	float intSpec = max(dot(h,n), 0.0);	
		        spec2 = specular * pow(intSpec, shininess);
		  }  
		  final_light2= (intensity2* diffuse +spec2) ;   
		}


		


			if(enable_texture>0){
				tempcolor = texture2D(texture, tex);
			}
			if(is_cone>0){
  				final_light4 = 0.25 * texture2D(texture,tex);
  			}

  			frag_color = (final_light1 + final_light2 + final_light3 + final_light4)*tempcolor + ambient;



  	}
  	else
  	{
  		frag_color = texture2D(texture,tex);
  	}



}

