import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.control.ToggleGroup;
import javafx.scene.Scene;
import javafx.scene.layout.TilePane;
import javafx.scene.control.RadioButton;
import javafx.scene.control.CheckBox;
import javafx.scene.control.Label;
import javafx.scene.layout.VBox;
import javafx.scene.layout.HBox;
import javafx.geometry.Insets;
import javafx.geometry.Pos;

public class CellSolutions extends Application
{
   final int PLAN_A_NUM = 1;
   final int PLAN_B_NUM = 2;
   final int PLAN_C_NUM = 3;
   final int MODEL_100_NUM = 1;
   final int MODEL_110_NUM = 2;
   final int MODEL_200_NUM = 3;
   final int APPLICATION_WIDTH = 630;
   final int APPLICATION_HEIGHT = 155;
   Cart cart;
   Label monthlyCostLabel;
   Label initialCostLabel;
   Label totalCostLabel;
   CheckBox insuranceCheckBox;
   CheckBox hotspotCheckBox;
   
   public static void main(String[] args)
   {
      launch(args);
   }
   
   public void start(Stage stage)
   {
      cart = new Cart();
      TilePane tile = buildTilePane();
      calculateTotalBill();
      
      Scene seeBillScene = new Scene(tile, APPLICATION_WIDTH, APPLICATION_HEIGHT);
      stage.setScene(seeBillScene);
      
      stage.show();
   }
   
   private TilePane buildTilePane()
   {
      VBox planVBox = buildPlansVBox();
      VBox modelVBox = buildModelsVBox();
      VBox extraOptionsVBox = buildExtraOptionsVBox();
      initialCostLabel = new Label("");
      monthlyCostLabel = new Label("");
      totalCostLabel = new Label("");
      
      HBox selectionHBox = buildSelectionHBox(planVBox, modelVBox, extraOptionsVBox);
      VBox costLabelsVBox = buildCostLabelsVBox(initialCostLabel, monthlyCostLabel, totalCostLabel);
      
      TilePane tilePane = new TilePane();
      tilePane.getChildren().add(selectionHBox);
      tilePane.getChildren().add(costLabelsVBox);
      
      return tilePane;
   }
   
   private HBox buildSelectionHBox(VBox planVBox, VBox modelVBox, VBox optionsVBox)
   {
      HBox selectionHBox = new HBox();
      selectionHBox.setPadding(new Insets(15, 5, 15, 5));
      selectionHBox.setSpacing(25);
      selectionHBox.setAlignment(Pos.CENTER_LEFT);
      
      selectionHBox.getChildren().add(planVBox);
      selectionHBox.getChildren().add(modelVBox);
      selectionHBox.getChildren().add(optionsVBox);
      
      return selectionHBox;
   }
   
   private VBox buildCostLabelsVBox(Label initialCostLabel, Label monthlyCostLabel, Label totalCostLabel)
   {
      VBox costLabelsVBox = new VBox();
      costLabelsVBox.setPadding(new Insets(15, 5, 15, 5));
      costLabelsVBox.setAlignment(Pos.CENTER_LEFT);
      
      costLabelsVBox.getChildren().add(initialCostLabel);
      costLabelsVBox.getChildren().add(monthlyCostLabel);
      costLabelsVBox.getChildren().add(totalCostLabel);
      
      return costLabelsVBox;
   }
   
   private VBox buildPlansVBox()
   {
      RadioButton planARadioButton = new RadioButton("8 GB for $45 per month");
      RadioButton planBRadioButton = new RadioButton("16 GB for $65 per month");
      RadioButton planCRadioButton = new RadioButton("20 GB for $99 per month");
      planARadioButton.setSelected(true);
      
      ToggleGroup planToggleGroup = new ToggleGroup();
      planARadioButton.setToggleGroup(planToggleGroup);
      planBRadioButton.setToggleGroup(planToggleGroup);
      planCRadioButton.setToggleGroup(planToggleGroup);
      
      planARadioButton.setOnAction(event -> updatePlan(PLAN_A_NUM));
      planBRadioButton.setOnAction(event -> updatePlan(PLAN_B_NUM));
      planCRadioButton.setOnAction(event -> updatePlan(PLAN_C_NUM));
      
      VBox planVBox = new VBox();
      planVBox.getChildren().add(planARadioButton);
      planVBox.getChildren().add(planBRadioButton);
      planVBox.getChildren().add(planCRadioButton);
      
      return planVBox;
   }
   
   private VBox buildModelsVBox()
   {
      RadioButton model100RadioButton = new RadioButton("Model 100 for $299.95");
      RadioButton model110RadioButton = new RadioButton("Model 110 for $399.95");
      RadioButton model200RadioButton = new RadioButton("Model 200 for $499.95");
      model100RadioButton.setSelected(true);
      
      ToggleGroup modelToggleGroup = new ToggleGroup();
      model100RadioButton.setToggleGroup(modelToggleGroup);
      model110RadioButton.setToggleGroup(modelToggleGroup);
      model200RadioButton.setToggleGroup(modelToggleGroup);
      
      model100RadioButton.setOnAction(event -> updatePhoneModel(MODEL_100_NUM));
      model110RadioButton.setOnAction(event -> updatePhoneModel(MODEL_110_NUM));
      model200RadioButton.setOnAction(event -> updatePhoneModel(MODEL_200_NUM));
      
      VBox modelVBox = new VBox();
      modelVBox.getChildren().add(model100RadioButton);
      modelVBox.getChildren().add(model110RadioButton);
      modelVBox.getChildren().add(model200RadioButton);
      
      return modelVBox;
   }
   
   private VBox buildExtraOptionsVBox()
   {
      insuranceCheckBox = new CheckBox("Phone Replacement Insurance for $5 per month");
      hotspotCheckBox = new CheckBox("WiFi HotSpot Capability for $10 per month");
      
      insuranceCheckBox.setOnAction(event -> updateHasInsurance(insuranceCheckBox.isSelected()));
      hotspotCheckBox.setOnAction(event -> setHasHotspot(hotspotCheckBox.isSelected()));
      
      VBox extraOptionsVBox = new VBox();
      extraOptionsVBox.getChildren().add(insuranceCheckBox);
      extraOptionsVBox.getChildren().add(hotspotCheckBox);
      
      return extraOptionsVBox;
   }
   
   private void updatePlan(int planNum)
   {
      cart.setPlan(planNum);
      
      calculateTotalBill();
   }
   
   private void updatePhoneModel(int phoneModelNum)
   {
      cart.setPhoneModel(phoneModelNum);
      
      calculateTotalBill();
   }
   
   private void updateHasInsurance(boolean insurance)
   {
      cart.setHasInsurance(insurance);
      
      calculateTotalBill();
   }
   
   private void setHasHotspot(boolean hotspot)
   {
      cart.setHasHotspot(hotspot);
      
      calculateTotalBill();
   }
   
   private void calculateTotalBill()
   {
      initialCostLabel.setText("Initial Cost: $" + convertAndFormatDoubleToString(cart.getInitialCost()));
      monthlyCostLabel.setText("Monthly Cost: $" + convertAndFormatDoubleToString(cart.getMonthlyCost()));
      totalCostLabel.setText("Total Cost (Monthly + Initial): $" + convertAndFormatDoubleToString(cart.getTotalCost()));
   }
   
   private String convertAndFormatDoubleToString(double num)
   {
      return String.format("%.2f", num);
   }
}