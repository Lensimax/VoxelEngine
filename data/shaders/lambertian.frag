#version 330

out vec4 bufferColor;


uniform vec4 color;
uniform float indexOfRefraction;
uniform float specularDegree;
uniform float lightIntensity;


in vec4 lightVec;
in vec4 normal;
in vec4 normalView;
in vec4 eyeView;

float pow2AbsDiv(float a, float b){
	if(b != 0){
		return abs((a/b)*(a/b));
	} else {
		return 0.001;
	}
}

/*
indexOfRefraction = eta
teta = dot(H, L)

*/

float fresnelCoef(float teta, float eta){

	float ci = sqrt(eta*eta - sin(teta)*sin(teta));

	float fs = pow2AbsDiv(cos(teta) - ci, cos(teta) + ci);

	float fp = pow2AbsDiv(eta*eta*cos(teta) - ci, eta*eta*cos(teta) + ci );


	return (fs + fp)/2.0;
}


vec4 phong(vec4 vcolor, float shininess, vec4 n, vec4 e, vec4 l, float eta){

	const bool blinnPhong = true;


	/* ambient lighting */
    const float ambientReflectionFactor = 0.2;
    vec4 ambientColor = ambientReflectionFactor * vcolor * lightIntensity;

    /* Diffuse lighting */
    const float diffuseRefletionFactor = 0.5;
    vec4 diffuseColor = diffuseRefletionFactor * vcolor * max(dot(n , l), 0) * lightIntensity;

	/* Specular Lighting */
    vec4 reflectedVector = reflect(l, n);
    const float specReflectionFactor = 1.2;
    // float maxVal = 0.0;
    float normed = length(l + e);
    vec4 H =(l+e)/normed;


    /*if(!blinnPhong){
        maxVal = pow(max( dot(reflectedVector,e),0), shininess);
    } else {
        maxVal = pow(max( dot(n, H),0), 4*shininess);
        float f0 = pow(1-eta, 2)/pow(1+eta, 2);
        fresnelFactor = f0 + (1 - f0)*pow((1-dot(H, e)), 5);
    }*/

	float maxVal = pow(max( dot(n, H),0.0), shininess);

    vec4 specularColor = fresnelCoef(dot(H, l), eta) * vcolor * maxVal * lightIntensity;

	// vec4 specularColor = vcolor * pow(max(dot(reflect(l,n),e),0.0),shininess) * lightIntensity;


	// return diffuseColor;
	// return ambientColor;
	// return specularColor;
	return specularColor + ambientColor + diffuseColor;
}



void main(){


	if(lightVec != vec4(0.0,0.0,0.0,1.0)){

		// normal / view and light directions (in camera space)
		vec4 n = normalize(normalView);
		vec4 e = normalize(eyeView);
		vec4 l = normalize(lightVec);


		// bufferColor = color;
		bufferColor = phong(color, specularDegree, n, e, l, indexOfRefraction);
	} else {
		bufferColor = color;
	}
}
