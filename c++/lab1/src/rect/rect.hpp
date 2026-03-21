class Rect{
private:
    // int left, right, top, bottom;
    int x, y, width, height;

public:
    Rect();
    Rect(int left, int top, int right, int bottom);
    Rect(const Rect& other);

    int get_left() const;
    int get_top() const;
    int get_right() const;
    int get_bottom() const;

    void set_all(int left, int right, int top, int bottom);

    void inflate(int amount);                              
    void inflate(int dw, int dh);                          
    void inflate(int d_left, int d_right, int d_top, int d_bottom);

    void move(int dx, int dy = 0); 

    int get_width() const;
    int get_height() const;
    int get_square() const;

    void set_width(int w);
    void set_height(int h);

    ~Rect();
};

Rect bounding_rect(Rect r1, Rect r2);

void print_rect(const Rect &r);