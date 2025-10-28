import javafx.application.Application;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;
import java.io.FileInputStream;

public class PlayableTicTacToe extends Application {

    private char currentPlayer = 'X';
    private char[][] board = new char[3][3];
    private Image xImage, oImage;

    @Override
    public void start(Stage primaryStage) throws Exception {
        xImage = new Image(new FileInputStream("X.jpg"));
        oImage = new Image(new FileInputStream("O.jpg"));

        GridPane grid = new GridPane();
        grid.setAlignment(Pos.CENTER);
        grid.setHgap(10);
        grid.setVgap(10);

        // Create 3x3 buttons (ImageViews)
        ImageView[][] cells = new ImageView[3][3];

        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                ImageView cell = new ImageView();
                cell.setFitHeight(100);
                cell.setFitWidth(100);
                int r = row;
                int c = col;

                // handle click
                cell.setOnMouseClicked(e -> handleMove(cells, r, c));

                grid.add(cell, col, row);
                cells[row][col] = cell;
            }
        }

        Scene scene = new Scene(grid, 350, 350);
        primaryStage.setTitle("Playable Tic Tac Toe");
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    private void handleMove(ImageView[][] cells, int row, int col) {
        if (board[row][col] != '\0') return; // already filled

        board[row][col] = currentPlayer;
        cells[row][col].setImage(currentPlayer == 'X' ? xImage : oImage);

        if (checkWin(currentPlayer)) {
            showAlert("Player " + currentPlayer + " wins!");
            resetGame(cells);
            return;
        } else if (isBoardFull()) {
            showAlert("It's a draw!");
            resetGame(cells);
            return;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X'; // switch turn
    }

    private boolean checkWin(char player) {
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
            if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
        }
        if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
        if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;

        return false;
    }

    private boolean isBoardFull() {
        for (int r = 0; r < 3; r++)
            for (int c = 0; c < 3; c++)
                if (board[r][c] == '\0')
                    return false;
        return true;
    }

    private void resetGame(ImageView[][] cells) {
        board = new char[3][3];
        for (int r = 0; r < 3; r++)
            for (int c = 0; c < 3; c++)
                cells[r][c].setImage(null);
        currentPlayer = 'X';
    }

    private void showAlert(String message) {
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle("Game Over");
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.showAndWait();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
