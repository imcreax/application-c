#include "equipment.h"



enum
{
	EID,
	ENOM,
	EJJ,
	EDISPONIBLE,
	EETAT,
	COLUMNS
};


void afficherequipment(GtkTreeView *liste)
{
GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter ;
    GtkListStore *store;
    agent a;
    store=NULL;
    FILE *f;
    store=GTK_LIST_STORE(gtk_tree_view_get_model(liste));
    if(store==NULL){
        
        renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("Id equipment",renderer,"text",EID,NULL);
        gtk_tree_view_append_column(liste,column);

        renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("Nom",renderer,"text",ENOM,NULL);
        gtk_tree_view_append_column(liste,column);

        renderer=gtk_cell_renderer_text_new();
  
        column=gtk_tree_view_column_new_with_attributes("Quantite",renderer,"text",EJJ,NULL);
        gtk_tree_view_append_column(liste,column);

	renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("Disponible",renderer,"text",EDISPONIBLE,NULL);
        gtk_tree_view_append_column(liste,column);
	
	renderer=gtk_cell_renderer_text_new();
        column=gtk_tree_view_column_new_with_attributes("etat",renderer,"text",EETAT,NULL);
        gtk_tree_view_append_column(liste,column);

    }
          
    store=gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_INT,G_TYPE_STRING,G_TYPE_STRING);
    f=fopen("equipment.txt","r");
    if(f==NULL){return;}
    else
    {
                 f=fopen("equipment.txt","a+");
         while(fscanf(f,"%s %s %d %s %s\n",a.idag, a.nom_ag,  &a.Quantite.jj, a.Disponible,a.etat)!=EOF)
         {
            gtk_list_store_append(store,&iter);
            gtk_list_store_set(store,&iter,0,a.idag,1,a.nom_ag,2,a.Quantite.jj,3,a.Disponible,4,a.etat,-1);
         }
     fclose(f);
     gtk_tree_view_set_model(liste,GTK_TREE_MODEL(store));
     g_object_unref(store);
    }

}
int ajoutequipment(agent a) {
    FILE *f;
 f= fopen("equipment.txt", "a+");
    if (f != NULL) {
        fprintf(f, "%s %s %d %s %s\n",a.idag, a.nom_ag, a.Quantite.jj,  a.Disponible,a.etat);
        fclose(f);
        return 1;
    } else {
        return 0;
    }
}
int modiferequipment(agent a) {
    int tr = 0;
    agent b;
    FILE *f = fopen("equipment.txt", "r");
    FILE *f2 = fopen("new.txt", "a+");
   if(f==NULL || f2==NULL)
return 0;
else
    {
while(fscanf(f,"%s %s %d %s %s\n",b.idag, b.nom_ag, &b.Quantite.jj,  b.Disponible,b.etat)!=EOF)
{
if(strcmp(b.idag,a.idag)==0)
        
	fprintf(f2,"%s %s %d %s %s\n",a.idag, a.nom_ag, a.Quantite.jj,  a.Disponible,a.etat);
else

  	fprintf(f2,"%s %s %d %s %s\n",b.idag, b.nom_ag, b.Quantite.jj,  b.Disponible,b.etat);

}
        fclose(f);
        fclose(f2);
remove("equipment.txt");
rename("new.txt", "equipment.txt");
        return 1;
    }

}


int supprimerequipment(char idag[]) {
    int tr = 0;
    agent D;
    FILE *f = fopen("equipment.txt", "r");
    FILE *f2 = fopen("new.txt", "a+");
     if(f==NULL || f2==NULL)
return 0;
else
    {
        while (fscanf(f, "%s %s %d %s %s\n",D.idag, D.nom_ag,  &D.Quantite.jj, D.Disponible,D.etat) != EOF) {
            if (strcmp(D.idag, idag) == 0) 
                tr = 1;
             else 
                fprintf(f2, "%s %s %d %s %s\n",D.idag, D.nom_ag,  D.Quantite.jj, D.Disponible,D.etat);
            
        }
    
    fclose(f);
    fclose(f2);
    remove("equipment.txt");
    rename("new.txt", "equipment.txt");
    if(tr==1)
        return 1;
else
	return 0;
    }

}

agent* chercherequipment(char idag[]) {
    agent* D = malloc(sizeof(agent));
    int t = 0;
    FILE* f = fopen("equipment.txt", "r");

    if (f == NULL)
        return NULL;
    else {
        while (fscanf(f, "%s %s %d %s %s\n",D->idag, D->nom_ag, &D-> Quantite.jj, D->Disponible,D->etat) != EOF) {
            if (strcmp(D->idag, idag) == 0){
                t = 1;
		break;}
        }

        fclose(f);

        if (t == 1)
            return D;
        else {
            free(D);  
            return NULL;
        }
 
    }}





