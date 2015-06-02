#version 110

varying vec3 normal,viewVec,reflectVec[3],lightDir[3];

void main(){

	vec3 vertexPositionInCameraCoordinates = vec3(gl_ModelViewMatrix * gl_Vertex);  // camera position
	gl_TexCoord[0] = gl_MultiTexCoord0;												// texture vertex
	viewVec = normalize(vec3(0,0,0) - vertexPositionInCameraCoordinates); // ;)		//view (V)
	normal = normalize (gl_NormalMatrix * gl_Normal);								// to get normal
	//lightDir = normalize( vec3(gl_LightSource[0].position) - vertexPositionInCameraCoordinates);	// light direction
	//reflectVec = normalize(reflect(-lightDir, normal)); 						// to get reflect (R)

	for (int i=0; i<3; ++i){
		lightDir[i] = normalize( vec3(gl_LightSource[i].position) - vertexPositionInCameraCoordinates);
		reflectVec[i] = normalize(reflect(-lightDir[i], normal));
	}

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;						// to get vertex
} 