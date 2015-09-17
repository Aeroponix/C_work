/*
//
//  memory-game.c
//
//	Created By: Adam Lindsey
//
//
//
*/

#include <gtk/gtk.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "deck.h"

/*  need global variables to keep track of game status
	has one card been clicked?
/**/
gboolean clicked = FALSE;

/* last image clicked on /**/
GtkImage *last_image;

/* last event_box clicked on */
GtkWidget *last_clicked;

/* widget label that holds score /**/
GtkLabel *score;

/* the current score /**/
int scorecard = 0;

/* the deck of cards /**/
struct Deck deck;


/*
This function will delay and pause the action
of other functions.
/**/
static void
delay()
{
    long pause;
    clock_t now,then;

    pause = 250*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}

/*
This function will use the GTK to flip the card image
/**/
static gboolean changeImage (GtkWidget      *image,
                             GtkImage       *data)
{
  gtk_image_set_from_file(data,(char*)gtk_widget_get_name(image));
  return TRUE;
}

/*
This function will be the onclick event handlers are below
/**/
static gboolean 
button_press_callback (GtkWidget      *image,
                       GdkEventButton *event,
                       GtkImage       *data)
{
  changeImage(image,data);
  if(clicked) {
    const char* name1 = gtk_widget_get_name(last_clicked);
    const char* name2 = gtk_widget_get_name(image);
    int counter = 0;
    if(name1==name2) return FALSE;
    if(name1[7]==name2[7]) counter++;
    if(name1[8]==name2[8]) counter++;
    if(name1[9]==name2[9]) counter++;
    if(counter>0) {
	g_signal_handlers_disconnect_by_func(G_OBJECT(image), G_CALLBACK(button_press_callback), data);
	g_signal_handlers_disconnect_by_func(G_OBJECT(last_clicked), G_CALLBACK(button_press_callback), last_image);
	scorecard = scorecard + counter;
    }
    else
    {
    	gtk_image_set_from_file(last_image,"assets/back-blue.gif");
    	gtk_image_set_from_file(data,"assets/back-blue.gif");
        scorecard--;
    }
    gchar *my_string = g_strdup_printf("Score: %i", scorecard);
    gtk_label_set_text(score,my_string);

    clicked=FALSE;
    
    //next line makes a gtkwidget invisible to user
    //gtk_widget_hide(image);

    }
    else 
    {
    //next line used for debugging to see image file path
    //printf(gtk_widget_get_name(image));
    last_image = data;
    last_clicked = image;
  
    //this next line prints the coordinates of an image click on the game board
    //g_print ("Event box clicked at coordinates %f,%f\n", event->x, event->y);
    
    //let game know that first card has been turned over
    clicked=TRUE;
  }
    // Returning TRUE means we handled the event, so the signal
    // emission should be stopped (don’t call any further callbacks
    // that may be connected). Return FALSE to continue invoking callbacks.
    return TRUE;
}

/* 
This function will be the method to create clickable image event_boxes
/**/
static GtkWidget* 
create_image(void)
{
  GtkWidget *image;
  GtkWidget *event_box;

  image = gtk_image_new_from_file ("assets/back-blue.gif");

  event_box = gtk_event_box_new ();

  gtk_container_add (GTK_CONTAINER (event_box), image);

  g_signal_connect (G_OBJECT (event_box),
                    "button_press_event",
                    G_CALLBACK (button_press_callback),
                    image);

  return event_box;
}

/* 
This function will create the deck object
/**/
static void 
createDeck() 
{
    int i;
    //loop for creating card filenames
    for(i=0; i<52; i++) 
    {
	//variable for constructing the filename for each card    	
	char filename[14];

	//now construct filename for each card
	filename[0] = 'a';
	filename[1] = 's';
	filename[2] = 's';
	filename[3] = 'e';
	filename[4] = 't';
	filename[5] = 's';
	filename[6] = '/';

	if(i<13) filename[7]='C';
	else if(i<26) filename[7]='D';
	else if(i<39) filename[7]='H';
	else filename[7]='S';

	if(i%13==0) filename[8]='2';
	else if(i%13==1) filename[8]='3';
	else if(i%13==2) filename[8]='4';
	else if(i%13==3) filename[8]='5';
	else if(i%13==4) filename[8]='6';
	else if(i%13==5) filename[8]='7';
	else if(i%13==6) filename[8]='8';
	else if(i%13==7) filename[8]='9';
	else if(i%13==8) filename[8]='T';
	else if(i%13==9) filename[8]='J';
	else if(i%13==10) filename[8]='Q';
	else if(i%13==11) filename[8]='K';
	else filename[8] = 'A';

	if(i<13) filename[9]='B';
	else if(i<39) filename[9]='R';
	else filename[9]='B';

	filename[10] = '.';
	filename[11] = 'g';
	filename[12] = 'i';
	filename[13] = 'f';
	
	//create the filename in each card
	strcpy(deck.cards[i].file,filename);
    }//end create deck filename loop

    //loop for creating card type
    for(i=0;i<52;i++) 
    {
	int suit;
	if(i<13) suit=0;
	else if(i<26) suit=1;
	else if(i<39) suit=2;
	else suit=3;
	//put color in each card
	deck.cards[i].type=suit;
    }

    //loop for creating card values
    for(i=0;i<52;i++) 
    {
	int val;
	if(i%13==0) val=0;
	else if(i%13==1) val=1;
	else if(i%13==2) val=2;
	else if(i%13==3) val=3;
	else if(i%13==4) val=4;
	else if(i%13==5) val=5;
	else if(i%13==6) val=6;
	else if(i%13==7) val=7;
	else if(i%13==8) val=8;
	else if(i%13==9) val=9;
	else if(i%13==10) val=10;
	else if(i%13==11) val=11;
	else val = 12;

	//put value in each card
	deck.cards[i].value = val;
    }

    //loop for creating card colors
    for(i=0;i<52;i++) 
    {
	int col;
	if(i<13) col=0;
	else if(i<39) col=1;
	else col=0;

	//put color in each card
	deck.cards[i].color=col;
    }
}

/*
This function will shuffle the global deck object
/**/
void 
shuffleDeck() 
{
    int i;
    //shuffle the deck twice for ultimate randomness
    for(i=0;i<52;i++) 
    {
	srand(time(NULL));
	//print functions for testing
	//printf("%d",deck.cards[i].type);
	//printf("%d",deck.cards[i].value);
	//printf("%d",deck.cards[i].color);
	//printf(deck.cards[i].file);

	int j;
	for(j=0;j<52;j++) 
	{
	  int r = rand()%52;
	  struct Card temp;
	  temp = deck.cards[i];
	  deck.cards[i] = deck.cards[j];
	  deck.cards[j] = deck.cards[r];
	  deck.cards[r] = temp;
	}
    }//end shuffle deck loop
}

/*
This function will create the game
/**/
static GtkWidget* 
create_game() 
{
    //widgets for cards
    GtkWidget *image00, *image01, *image02, *image03, *image04, *image05, *image06, 
	*image07, *image08, *image09, *image10, *image11, *image12,
	*image13, *image14, *image15, *image16, *image17, *image18, *image19, 
	*image20, *image21, *image22, *image23, *image24, *image25,
	*image26, *image27, *image28, *image29, *image30, *image31, *image32, 
	*image33, *image34, *image35, *image36, *image37, *image38,
    	*image39, *image40, *image41, *image42, *image43, *image44, *image45, 
	*image46, *image47, *image48, *image49, *image50, *image51;

    //widgets for layout boxes
    GtkWidget *hbox0,*hbox1,*hbox2,*hbox3,*vbox;

    //widgets for buttons
    GtkWidget *quit_btn;

    //set the button objects
    quit_btn = gtk_button_new_with_label("Quit Game");
 
    //set all of the image objects
    image00 = create_image();
    gtk_widget_set_name(image00,deck.cards[0].file);
    image01 = create_image();
    gtk_widget_set_name(image01,deck.cards[1].file);
    image02 = create_image();
    gtk_widget_set_name(image02,deck.cards[2].file);
    image03 = create_image();
    gtk_widget_set_name(image03,deck.cards[3].file);
    image04 = create_image();
    gtk_widget_set_name(image04,deck.cards[4].file);
    image05 = create_image();
    gtk_widget_set_name(image05,deck.cards[5].file);
    image06 = create_image();
    gtk_widget_set_name(image06,deck.cards[6].file);
    image07 = create_image();
    gtk_widget_set_name(image07,deck.cards[7].file);
    image08 = create_image();
    gtk_widget_set_name(image08,deck.cards[8].file);
    image09 = create_image();
    gtk_widget_set_name(image09,deck.cards[9].file);
    image10 = create_image();
    gtk_widget_set_name(image10,deck.cards[10].file);
    image11 = create_image();
    gtk_widget_set_name(image11,deck.cards[11].file);
    image12 = create_image();
    gtk_widget_set_name(image12,deck.cards[12].file);
    image13 = create_image();
    gtk_widget_set_name(image13,deck.cards[13].file);
    image14 = create_image();
    gtk_widget_set_name(image14,deck.cards[14].file);
    image15 = create_image();
    gtk_widget_set_name(image15,deck.cards[15].file);
    image16 = create_image();
    gtk_widget_set_name(image16,deck.cards[16].file);
    image17 = create_image();
    gtk_widget_set_name(image17,deck.cards[17].file);
    image18 = create_image();
    gtk_widget_set_name(image18,deck.cards[18].file);
    image19 = create_image();
    gtk_widget_set_name(image19,deck.cards[19].file);
    image20 = create_image();
    gtk_widget_set_name(image20,deck.cards[20].file);
    image21 = create_image();
    gtk_widget_set_name(image21,deck.cards[21].file);
    image22 = create_image();
    gtk_widget_set_name(image22,deck.cards[22].file);
    image23 = create_image();
    gtk_widget_set_name(image23,deck.cards[23].file);
    image24 = create_image();
    gtk_widget_set_name(image24,deck.cards[24].file);
    image25 = create_image();
    gtk_widget_set_name(image25,deck.cards[25].file);
    image26 = create_image();
    gtk_widget_set_name(image26,deck.cards[26].file);
    image27 = create_image();
    gtk_widget_set_name(image27,deck.cards[27].file);
    image28 = create_image();
    gtk_widget_set_name(image28,deck.cards[28].file);
    image29 = create_image();
    gtk_widget_set_name(image29,deck.cards[29].file);
    image30 = create_image();
    gtk_widget_set_name(image30,deck.cards[30].file);
    image31 = create_image();
    gtk_widget_set_name(image31,deck.cards[31].file);
    image32 = create_image();
    gtk_widget_set_name(image32,deck.cards[32].file);
    image33 = create_image();
    gtk_widget_set_name(image33,deck.cards[33].file);
    image34 = create_image();
    gtk_widget_set_name(image34,deck.cards[34].file);
    image35 = create_image();
    gtk_widget_set_name(image35,deck.cards[35].file);
    image36 = create_image();
    gtk_widget_set_name(image36,deck.cards[36].file);
    image37 = create_image();
    gtk_widget_set_name(image37,deck.cards[37].file);
    image38 = create_image();
    gtk_widget_set_name(image38,deck.cards[38].file);
    image39 = create_image();
    gtk_widget_set_name(image39,deck.cards[39].file);
    image40 = create_image();
    gtk_widget_set_name(image40,deck.cards[40].file);
    image41 = create_image();
    gtk_widget_set_name(image41,deck.cards[41].file);
    image42 = create_image();
    gtk_widget_set_name(image42,deck.cards[42].file);
    image43 = create_image();
    gtk_widget_set_name(image43,deck.cards[43].file);
    image44 = create_image();
    gtk_widget_set_name(image44,deck.cards[44].file);
    image45 = create_image();
    gtk_widget_set_name(image45,deck.cards[45].file);
    image46 = create_image();
    gtk_widget_set_name(image46,deck.cards[46].file);
    image47 = create_image();
    gtk_widget_set_name(image47,deck.cards[47].file);
    image48 = create_image();
    gtk_widget_set_name(image48,deck.cards[48].file);
    image49 = create_image();
    gtk_widget_set_name(image49,deck.cards[49].file);
    image50 = create_image();
    gtk_widget_set_name(image50,deck.cards[50].file);
    image51 = create_image();
    gtk_widget_set_name(image51,deck.cards[51].file);

    //set up layout boxes
    hbox0 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 13);
    hbox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 13);
    hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 13);
    hbox3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 13);
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    //pack the clickable images & buttons into the layout boxes
    gtk_box_pack_start(GTK_BOX(hbox0), image00, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox0), image01, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox0), image02, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox0), image03, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox0), image04, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox0), image05, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox0), image06, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox0), image07, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox0), image08, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox0), image09, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox0), image10, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox0), image11, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox0), image12, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox1), image13, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox1), image14, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox1), image15, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox1), image16, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox1), image17, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox1), image18, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox1), image19, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox1), image20, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox1), image21, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox1), image22, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox1), image23, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox1), image24, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox1), image25, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox2), image26, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox2), image27, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox2), image28, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox2), image29, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox2), image30, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox2), image31, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox2), image32, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox2), image33, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox2), image34, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox2), image35, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox2), image36, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox2), image37, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox2), image38, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox3), image39, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox3), image40, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox3), image41, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox3), image42, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox3), image43, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox3), image44, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox3), image45, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox3), image46, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox3), image47, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox3), image48, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox3), image49, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox3), image50, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox3), image51, FALSE, FALSE, 1);
    
    //then pack those boxes into more boxes
    gtk_box_pack_start(GTK_BOX(vbox), hbox0, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(vbox), hbox1, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(vbox), hbox2, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(vbox), hbox3, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(score), FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(vbox), quit_btn, FALSE, FALSE, 1);

    //and throw a quit button in there too
    g_signal_connect(G_OBJECT(quit_btn), "clicked", G_CALLBACK(gtk_main_quit), NULL);

    //return the created game board
    return vbox;
}

/*
This function will create a new game by calling create_game()
/**/
static gboolean 
newGame(GtkWidget      *btn,
        GdkEventButton *event,
        GtkWidget      *data) 
{
   data = create_game();
   return TRUE;
}//end newGame()


/*
This is the main program method
/**/
int
main( int argc, char *argv[])
{   
    //create the deck struct
    createDeck();

    //shuffle the deck struct
    shuffleDeck();
    
    //game widget
    GtkWidget *game;
    
    //game board widget
    GtkWidget *game_board;
    
    //widget button for new game
    GtkWidget *newGame_btn;

    //widget for layout boxes
    GtkWidget *xbox;

    GtkWidget *score_new;

    //initialize all gtk objects
    gtk_init(&argc, &argv);

    //set the button object
    newGame_btn = gtk_button_new_with_label("New Game");

    //set the score label
    gchar *my_string = g_strdup_printf("Score: %i", scorecard);
    score_new = gtk_label_new(my_string);
    score = GTK_LABEL(score_new);

    //set the game board object
    game = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(game), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(game), "Memory Game");
    gtk_window_set_resizable(GTK_WINDOW(game), FALSE);
    gtk_container_set_border_width(GTK_CONTAINER(game), 2);

    xbox = create_game();
    //gtk_container_add(GTK_CONTAINER(xbox),newGame_btn);
    
    game_board = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(game_board), xbox);
    //add the layout box to the bame board
    gtk_container_add(GTK_CONTAINER(game), game_board);

    //wire event handlers to widgets
    g_signal_connect(G_OBJECT(game), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(newGame_btn), "clicked", G_CALLBACK(newGame), game_board);
    gtk_widget_show_all(game);
    
    //start the game
    gtk_main();
    
    return 0;
}//end main()
