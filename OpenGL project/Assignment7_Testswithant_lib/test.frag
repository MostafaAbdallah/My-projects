#version 120

varying vec3 normal,viewVec,reflectVec[3],lightDir[3];
uniform sampler2D tex;
uniform int switch_light[4];

void main(){	

	vec3 norm,refl[3];
	float diffuseIntensity[3] ,specularIntensity[3] ;
	vec4 color = vec4(0.0);
	int j=0,k=0;

	norm = normalize (normal);
	
	/*refl = normalize(reflectVec);
    vec3 view = normalize(viewVec);

	diffuseIntensity = max(dot(norm,lightDir), 0.0);	
	
	if ( diffuseIntensity > 0.0 ){
		color += texture2D(tex,gl_TexCoord[0].st) /* vec4(0.7,0,0,0) * */ /* gl_LightSource[0].diffuse */ //* //diffuseIntensity;
		/*specularIntensity = max(dot(refl, view), 0.0);
		color += gl_LightSource[0].specular * pow (specularIntensity,gl_FrontMaterial.shininess);		
	}*/

	// try light0 only i = 0 , i < 1
	// try light1 only i = 1 , i < 2
	//then try both i = 0 , i < 2
	
	if (switch_light[0]==1){k=0;	j=1;}
	if (switch_light[1]==1){k=1;	j=2;}
	if (switch_light[2]==1){k=2;	j=3;}
	if (switch_light[3]==1){k=0;	j=3;}

	 for (int i=k; i<j; ++i){
		refl[i] = normalize(reflectVec[i]);
		vec3 view = normalize(viewVec);

		diffuseIntensity[i] = max(dot(norm,lightDir[i]), 0.0);

		if ( diffuseIntensity[i] > 0.0 ){
			//color += texture2D(tex,gl_TexCoord[0].st) /* vec4(0.7,0,0,0) * */ /* gl_LightSource[0].diffuse */ * diffuseIntensity[i];
			color +=  texture2D(tex,gl_TexCoord[0].st) *  gl_LightSource[i].diffuse * diffuseIntensity[i];
			specularIntensity[i] = max(dot(refl[i], view), 0.0);
			color += /*vec4(1,1,1,1) */ gl_LightSource[i].specular * pow (specularIntensity[i],gl_FrontMaterial.shininess);		
		}


	}

	gl_FragColor = color;
} 