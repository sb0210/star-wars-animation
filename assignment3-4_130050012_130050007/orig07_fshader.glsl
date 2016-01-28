#version 330

in vec3 normal;
in vec4 eye;
in vec4 COLOR;
in vec2 tex;

uniform mat4 viewMatrix;
uniform sampler2D texture;
uniform float b;
uniform float light1;//
uniform float light2;//
uniform float light3;
uniform float enable_texture;//

uniform vec4 diffuse;
uniform vec4 ambient;
uniform vec4 specular;
uniform float shininess;

out vec4 frag_color;

void main () 
{	
  // Defining Materials

	vec4 tempcolor= COLOR;

	if(b<0){

		  vec4 final_light1=vec4(0.0);
		  vec4 final_light2=vec4(0.0);
		  vec4 final_light3=vec4(0.0);
		  vec3 n = normalize(vec3(normal));	     

		  // Defining Light 1
		if(light2>0){
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

		if(light1 > 0){

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

  			frag_color = max((final_light1 + final_light2)*tempcolor, ambient);



  	}
  	else
  	{
  		frag_color = texture2D(texture,tex);
  	}

}

