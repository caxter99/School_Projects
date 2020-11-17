import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.control.Menu;
import javafx.scene.control.ToggleGroup;
import javafx.scene.layout.BorderPane;
import javafx.scene.control.RadioMenuItem;
import javafx.scene.Scene;
import javafx.scene.layout.VBox;
import javafx.scene.control.MenuBar;

public class CellSolutions extends Application
{
   
   public static void main(String[] args)
   {
      launch(args);
   }
   
   public void start(Stage stage)
   {
      Menu planMenu = new Menu("Text");
      
      RadioMenuItem planA = new RadioMenuItem("Plan A");
      RadioMenuItem planB = new RadioMenuItem("Plan B");
      RadioMenuItem planC = new RadioMenuItem("Plan C");
      planA.setSelected(true);
      
      ToggleGroup planToggleGroup = new ToggleGroup();
      planA.setToggleGroup(planToggleGroup);
      planB.setToggleGroup(planToggleGroup);
      planC.setToggleGroup(planToggleGroup);
      
      // set actions for each button and plan
      
      planMenu.getItems().add(planA);
      planMenu.getItems().add(planB);
      planMenu.getItems().add(planC);
      
      MenuBar mb = new MenuBar();
      mb.getMenus().add(planMenu);
      
      VBox vb = new VBox(mb);
      
      Scene seePhoneBillScene = new Scene(vb, 500, 500);
      
      stage.setScene(seePhoneBillScene);
      
      stage.show();
   }
}


// import javafx.application.Application;
// import javafx.stage.Stage;
// import javafx.scene.Scene;
// import javafx.scene.layout.Pane;
// import javafx.scene.shape.Circle;
// import javafx.util.Duration;
// import javafx.animation.TranslateTransition;
// 
// public class JavaFXBallDrop extends Application
// {
//    public static void main(String[] args)
//    {
//       launch(args);
//    }  // end main()
//    
//    public void start(Stage pStage)
//    {
//       // Constants for scene size
//       final double SWIDTH = 200.0;
//       final double SHEIGHT = 200.0;
//       
//       // Constants for the ball
//       final double STARTX = 100.0, STARTY = 40.0;
//       final double ENDX = 100.0, ENDY = 160.0;
//       final double RADIUS = 40.0;
//       // Constant for animation duration 
//       final double ONESEC = 1000.0;
//       
//       // Create the ball
//       Circle ball = new Circle(RADIUS);
//       // Transition object
//       TranslateTransition ttrans = new TranslateTransition(new Duration(ONESEC), ball);
//       ttrans.setFromX(STARTX);
//       ttrans.setFromY(STARTY);
//       ttrans.setToX(ENDX);
//       ttrans.setToY(ENDY);
//       // Add the ball to the pane
//       Pane pane = new Pane(ball);
//       // Create the scene and display it
//       Scene scene = new Scene(pane, SWIDTH, SHEIGHT);
//       pStage.setScene(scene);
//       pStage.setTitle("Animation of the Dropping Ball");
//       pStage.show();
//       // Play the transition
//       ttrans.play();
//    }  // end start()
// }  // end class