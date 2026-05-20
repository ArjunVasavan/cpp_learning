class player {
    int x, y;
    int speed;

    public:
    void move(int mx, int my) {
        x = mx;
        y = my;
    }
};



int main() {

    player p1; // we instantiated an player object
    p1.move(1,2);
}
