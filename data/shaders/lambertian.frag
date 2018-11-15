#version 330

out vec4 bufferColor;


uniform vec4 color;
uniform vec4 light;

uniform float specularDegree;


in vec4 normal;
in vec4 normalView;
in vec4 eyeView;


vec4 phong(vec4 vcolor, float shininess, vec4 n, vec4 e, vec4 l){

	const float lightIntensity = 200;
	const bool blinnPhong = true;
	const float eta = 100;


	/* ambient lighting */
    const float ambientReflectionFactor = 0.2;
    vec4 ambientColor = ambientReflectionFactor * vcolor * lightIntensity;

    /* Diffuse lighting */
    const float diffuseRefletionFactor = 0.5;
    vec4 diffuseColor = diffuseRefletionFactor * vcolor * max(dot(n , l), 0) * lightIntensity;

	/* Specular Lighting */
    vec4 reflectedVector = reflect(l, n);
    const float specReflectionFactor = 1.2;
    float maxVal = 0.0;
    float normed = length(l + e);
    float fresnelFactor = 1.0;
    vec4 H =(l+e)/normed;

    /*if(!blinnPhong){
        maxVal = pow(max( dot(reflectedVector,e),0), shininess);
    } else {
        maxVal = pow(max( dot(n, H),0), 4*shininess);
        float f0 = pow(1-eta, 2)/pow(1+eta, 2);
        fresnelFactor = f0 + (1 - f0)*pow((1-dot(H, e)), 5);
    }

    vec4 specularColor = specReflectionFactor * vcolor * fresnelFactor * lightIntensity;*/

	vec4 specularColor = vcolor * pow(max(dot(reflect(l,n),e),0.0),shininess) * lightIntensity;


	// return specularColor;
	// return ambientColor;
	return diffuseColor;
	// return specularColor + ambientColor + diffuseColor;
}


void main(){


	if(light != vec4(0.0,0.0,0.0,1.0)){

		// normal / view and light directions (in camera space)
		vec4 n = normalize(normalView);
		vec4 e = normalize(eyeView);
		vec4 l = normalize(light);


		// bufferColor = color;
		bufferColor = phong(color, specularDegree, n, e, l);
	} else {
		bufferColor = color;
	}
}
