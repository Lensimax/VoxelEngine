#version 330

out vec4 bufferColor;

in vec3 normal;

uniform vec4 color;

uniform vec3 light;

/*vec4 phong(vec3 myColor, float specDeg){
	const vec3 ambientColor  = vec3(0.1,0.1,0.1);
	const vec3 specular = vec3(0.9,0.9,0.9);

	// normal / view and light directions (in camera space)
	vec3 n = normalize(normalView);
	vec3 e = normalize(eyeView);
	vec3 l = normalize(lightVector);

	// diffuse and specular components of the phong shading model
	float diff = max(dot(l,n),0.0);
	float spec = pow(max(dot(reflect(l,n),e),0.0),specDeg);

	// final color
	vec3 color = ambientColor + diff*myColor + spec*specular;
	return vec4(color,1.0);
}*/


void main(){
	//bufferColor = vec4(1.0,1.0,0.0,1.0);
	/*light = Normalize(light);
	if(light == vec3(0.0,0.0,0.0)){
		bufferColor = color;
	} else { //  we do phong equation
		// bufferColor = phong(color, 0.5);
		bufferColor = vec3(0.0,1.0,0.0,1.0);
	}*/

	bufferColor = color;
}
