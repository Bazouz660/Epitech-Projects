#version 100

precision mediump float;

// Input vertex attributes (from vertex shader)
varying vec3 fragPosition;
varying vec2 fragTexCoord;
varying vec4 fragColor;
varying vec3 fragNormal;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// NOTE: Add here your custom variables

#define     MAX_LIGHTS              4
#define     LIGHT_DIRECTIONAL       0
#define     LIGHT_POINT             1

struct MaterialProperty {
    vec3 color;
    int useSampler;
    sampler2D sampler;
};

struct Light {
    int enabled;
    int type;
    vec3 position;
    vec3 target;
    vec4 color;
};

// Input lighting values
uniform Light lights[MAX_LIGHTS];
uniform vec4 ambient;
uniform vec3 viewPos;
uniform float fogDensity;

void main()
{
    // Texel color fetching from texture sampler
    vec4 texelColor = texture2D(texture0, fragTexCoord);

    // Check if the texel alpha is 0
    if (texelColor.a == 0.0f) discard;

    vec3 lightDot = vec3(0.0);
    vec3 normal = normalize(fragNormal);
    vec3 viewD = normalize(viewPos - fragPosition);
    vec3 specular = vec3(0.0);

    // NOTE: Implement here your fragment shader code

    for (int i = 0; i < MAX_LIGHTS; i++)
    {
        if (lights[i].enabled == 1)
        {
            vec3 light = vec3(0.0);

            if (lights[i].type == LIGHT_DIRECTIONAL) light = -normalize(lights[i].target - lights[i].position);
            if (lights[i].type == LIGHT_POINT) light = normalize(lights[i].position - fragPosition);

            float NdotL = max(dot(normal, light), 0.0);
            lightDot += lights[i].color.rgb * NdotL;

            float specCo = 0.0;
            if (NdotL > 0.0) specCo = pow(max(0.0, dot(viewD, reflect(-(light), normal))), 16.0); // Shine: 16.0
            specular += specCo;
        }
    }

    vec4 finalColor = (texelColor * colDiffuse) + vec4(specular, 0.0) * vec4(lightDot, 1.0);
    finalColor += texelColor * (ambient / 10.0);

    // Fog calculation
    float dist = length(viewPos - fragPosition);

    // Adjust the fog color
    const vec4 fogColor = vec4(0.5, 0.5, 0.5, 1.0);

    // Exponential fog
    float fogFactor = 1.0 - exp(-fogDensity * fogDensity * dist * dist);

    vec4 foggedColor = fogColor * pow(1.0 - fogFactor, 6.0);

    // Multiply the fogged color with the texel color
    foggedColor.rgb = mix(foggedColor.rgb, texelColor.rgb, 1.0 - fogFactor);

    // Multiply the fogged color with the final color
    //gl_FragColor = mix(finalColor, foggedColor, fogFactor);
    gl_FragColor = finalColor;
}
