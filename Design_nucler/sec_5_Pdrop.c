
void pressureDrop(void){

    double μ_w = find_μ(t_ci_h[0]);
    double μ_f = find_μ( (f_in + t_f_h[0]) / 2);
    double h = find_h(t_f_h[0]);
    double ρ = find_ρ(t_f_h[0]);
    
    double G = ρ * V;
    double ρ_in = find_ρ(f_in);
    double ρ_out = find_ρ(f_out_S);
    double f = (0.3164 / powf(Re,0.25)) * powf(μ_w/μ_f,0.6);

    double υ_in = find_υ(f_in);
    double υ_out = find_υ(f_out_S);


    printf("μ_w:%lf\n",μ_w);
    printf("μ_f:%lf\n",μ_f);
    printf("G:%lf\n",G);
    printf("f:%lf\n",f);


    d_P_a = 0;
    d_P_f = (f * L * powf(G,2)) / (2 * D_e * ρ);
    d_P_el = (ρ_in + ρ_out) / 2 * g * L;
    d_P_in = K_in * powf(G,2) * υ_in / 2;
    d_P_out = K_out * powf(G,2) * υ_out / 2;
    d_P_gr = K_gr * powf(G,2) * (υ_out + υ_in)/4;
    d_P =  d_P_f + d_P_a + d_P_el + d_P_in + d_P_out + d_P_gr;
}