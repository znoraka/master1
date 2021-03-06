#include <stdio.h>
#include "../lib_c/image_ppm.h"
#include "math.h"
#include "../lib_c/utils.h"

int seuil = 10;

void fill(OCTET *in, OCTET *blacks, int lignes, int colonnes) {
// 
	// int *blacks = malloc(lignes * colonnes * sizeof(int));
	int index;
	int sum = 0;
	int cpt = 0;

	for (index=0; index < lignes * colonnes; index++) {
		int val = in[index];
		if(val < seuil) {
			blacks[index] = 0;
		} else {
			blacks[index] = 1;
			sum += in[index];
			cpt++;
		}
	}

	sum /= cpt;

	for (index=0; index < lignes * colonnes; index++) {
		if(!blacks[index]) {
			in[index] = sum;
		}
	}
}

void dilater(OCTET *in, OCTET *out, int lignes, int colonnes) {

	int index;
	int bool = 1;

	for (index=0; index < lignes * colonnes; index++) {
		int val = in[index];
		int m = val;

		if(val < seuil) {
			int n = in[indexN(index, lignes, colonnes)];
			int s = in[indexS(index, lignes, colonnes)];
			int e = in[indexE(index, lignes, colonnes)];
			int w = in[indexW(index, lignes, colonnes)];
			int sum = 0;

			int t = 0;
			if(n > seuil) {t++;sum += n;}
			if(s > seuil) {t++;sum += s;}
			if(e > seuil) {t++;sum += e;}
			if(w > seuil) {t++;sum += w;}

			if(t) {
				m = sum / t;
			}
		}
		in[index] = m;				
	}
}

void eroder(OCTET *in, OCTET *out, int lignes, int colonnes) {

	int index;
	int bool = 1;

	for (index=0; index < lignes * colonnes; index++) {
		int val = in[index];
		int m = val;

		if(val < seuil) {
			out[indexN(index, lignes, colonnes)] = 0;
			out[indexS(index, lignes, colonnes)] = 0;
			out[indexE(index, lignes, colonnes)] = 0;
			out[indexW(index, lignes, colonnes)] = 0;
		} else {
			out[index] = in[index];
		}

	}
}


void fill2(OCTET *in, OCTET *out, int lignes, int colonnes) {
	eroder(in, out, lignes, colonnes);
	eroder(out, in, lignes, colonnes);
	dilater(in, out, lignes, colonnes);
	int index;
	int bool = 1;

	while (bool) {
		bool = 0;

		for (index=0; index < lignes * colonnes; index++) {
			int val = in[index];
			int m = val;

			if(val < seuil) {
				bool = 1;
				int n = in[indexN(index, lignes, colonnes)];
				int s = in[indexS(index, lignes, colonnes)];
				int e = in[indexE(index, lignes, colonnes)];
				int w = in[indexW(index, lignes, colonnes)];

				if(in[indexN(n, lignes, colonnes)] > seuil) {
					in[index] = in[indexN(index, lignes, colonnes)];
				}
				if(in[indexS(s, lignes, colonnes)] > seuil) {
					in[index] = in[indexS(index, lignes, colonnes)];
				}
				if(in[indexE(e, lignes, colonnes)] > seuil) {
					in[index] = in[indexE(index, lignes, colonnes)];
				}
				if(in[indexW(w, lignes, colonnes)] > seuil) {
					in[index] = in[indexW(index, lignes, colonnes)];
				}

			}
		}
	}
}


int main(int argc, char* argv[])
{
	char cNomImgLue[250];
	char out[250] = "out.pgm";

	int lignes, colonnes, nTaille, S;

	sscanf (argv[1],"%s",cNomImgLue);

	OCTET *ImgIn, *ImgOut;

	lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &lignes, &colonnes);
	nTaille = lignes * colonnes;

	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(cNomImgLue, ImgIn, lignes * colonnes);
	allocation_tableau(ImgOut, OCTET, nTaille);

	// dilater(ImgIn, ImgOut, lignes, colonnes);
	// ecrire_image_pgm(out, ImgIn, lignes, colonnes);

	fill2(ImgIn, ImgOut, lignes, colonnes);
	ecrire_image_pgm(out, ImgIn, lignes, colonnes);

	free(ImgIn);
	return 1;
}
